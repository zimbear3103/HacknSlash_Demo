# Combo chỉ nhận input trong window

Ngày kiểm tra: 19/09/2026. Quyết định: bỏ input bấm sớm; mỗi combo window nhận tối đa một lệnh nối đòn.

## Behavior đã sửa

- `GA_MeleeAttack`: LMB ngoài window chỉ đăng ký lại `WaitInputPress(false)`, không buffer.
- RMB chỉ được nhận khi `CurrentComboIndex == 2` và `bComboWindowOpen == true`; ngoài điều kiện này thì bỏ.
- Event `CombatWindow.Open` chỉ mở window, không tự tiêu thụ input cũ.
- `AdvanceCombo` / `AdvanceHeavyFinisher` vẫn đóng window ngay sau khi chọn next section. Lệnh đến sau không ghi đè lựa chọn.
- Một LMB bắt đầu combo từ idle vẫn chạy `Attack_01` như trước.

Trong `Attack_02`: LMB hợp lệ chọn `Attack_03`; RMB hợp lệ chọn `HeavyAttack`. Nếu không bấm trong window thì kết thúc sau `Attack_02`.

## Nguyên nhân và phạm vi

Trước sửa, input ngoài window được giữ bằng `bAttackBuffered` / `bHeavyBuffered`. Event Open dùng lại các cờ này để nối đòn. `CurrentComboIndex` còn được tăng ngay lúc chọn next section, trước khi animation hiện tại kết thúc; vì vậy input LMB dư ở cuối `Attack_01` có thể bị dùng để chọn luôn `Attack_03`.

Đã sửa hai kết nối exec và xóa 18 node thuộc các nhánh buffer trong Gameplay Ability Graph. Ba function graph `AdvanceCombo`, `AdvanceHeavyFinisher`, `CleanupMeleeAttack` không đổi. Giữ tên reflected variables cũ; các cờ buffer chỉ còn được reset, không còn đọc để quyết định combo.

Không đổi montage, vị trí notify, input mapping, damage hoặc C++. Các thay đổi `.uasset` khác đã có trước task này.

## Kiểm tra thực tế

Fixture: `/Game/Tests/Combat/BP_ComboWindowRegression`. Test chạy trong PIE trên `Map_Startup`, gọi `PressInputID` / `ReleaseInputID` của ASC hero thật, và kiểm tra chuỗi section từ AnimInstance thật. Input LMB = 3, RMB = 4 theo `EGDAbilityInputID` của project.

| Case | Input | Kết quả mong đợi | Trước | Sau |
| --- | --- | --- | --- | --- |
| 0 | LMB bắt đầu, spam LMB x8 trước window đầu | `Attack_01` | Fail: nối `Attack_02` | Pass |
| 1 | LMB đúng window đầu, spam RMB x8 ngay khi vào `Attack_02` | `Attack_01 → Attack_02` | Fail: nối heavy | Pass |
| 2 | LMB đúng cả hai window | `Attack_01 → Attack_02 → Attack_03` | Pass | Pass |
| 3 | LMB đúng window đầu, RMB đúng window thứ hai | `Attack_01 → Attack_02 → HeavyAttack` | Pass | Pass |
| 4 | Một LMB từ idle | `Attack_01` | Pass | Pass |
| 5 | Đã chọn `Attack_02`, spam LMB x8 trong phần còn lại của `Attack_01` | `Attack_01 → Attack_02` | Fail: nối `Attack_03` | Pass |
| 6 | RMB rồi LMB x8 trong cùng window của `Attack_02` | Heavy, giữ lựa chọn đầu | Pass | Pass |
| 7 | LMB rồi RMB x8 trong cùng window của `Attack_02` | `Attack_03`, giữ lựa chọn đầu | Pass | Pass |

Kết quả: trước sửa 5/8 pass, sau sửa 8/8 pass. Log nguyên bản: [Diagnostics/combo-window-regression-2026-09-19.json](Diagnostics/combo-window-regression-2026-09-19.json).

Blueprint compile với `warnings_as_errors=true` thành công. Kiểm tra pin graph xác nhận listener LMB được đăng ký lại sau cả input hợp lệ lẫn input bị bỏ. `git diff --check` pass. Đây là kiểm tra Blueprint và PIE local; chưa test multiplayer, packaged build hoặc đánh giá visual feel toàn bộ combo.

## Chạy lại

1. Mở `Map_Startup`, kéo `BP_ComboWindowRegression` vào level để test; không cần lưu map.
2. Bật PIE, không nhập input thủ công trong khoảng 45 giây.
3. Lọc Output Log bằng `[COMBO TEST]`; cần đủ 8 `PASS`, không có `FAIL`, và một `DONE`.
4. Stop PIE, xóa actor fixture khỏi level. Actor test của lượt sửa này đã được gỡ khỏi `Map_Startup`.

Nếu Editor đang ở background, tắt tạm `Use Less CPU when in Background` khi test để không bỏ lỡ window do Editor throttle; khôi phục thiết lập sau khi test. Lượt sửa này đã khôi phục thiết lập ban đầu.

Full DSL của fixture nằm tại `Content/Tests/Combat/bp_combowindowregression.dsl.txt`; dùng với `write_graph_dsl` của EditorToolset. Bản backup asset trước sửa và pin snapshots nằm trong `Saved/ComboWindowFix/`, không đưa vào Git.

## Lưu ý

- Bấm sớm không còn được giữ lại nên combo yêu cầu timing chính xác hơn. Timing window hiện tại được giữ nguyên.
- Spam có một lần bấm trúng window vẫn nối được đúng một đòn. Quy tắc này không có cooldown hay hình phạt dành riêng cho spam.
- Test fixture tự điều khiển hero khi được đặt trong level; chỉ đặt nó khi chạy regression.
