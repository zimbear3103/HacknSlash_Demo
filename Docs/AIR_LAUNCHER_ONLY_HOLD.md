# Launcher-only air hold

Yêu cầu ngày 2026-09-25: chỉ treo trên không khi đánh tiếp sau launcher trúng target. Nhảy thường rồi đánh phải giữ quỹ đạo rơi tự nhiên.

## Thay đổi gameplay

Asset: `/Game/GASDocumentation/Characters/Hero/Abilities/Attack/AirCombo/GA_AirAttack`, function `BeginAirHold`.

Trước sửa, `Sequence.Then0` luôn dừng Hero và đặt gravity về 0; `Then1` mới kiểm tra target. Vì vậy nhảy đánh không có launcher target vẫn bị khựng.

Sau sửa, toàn bộ phần giữ Hero và target chạy sau các điều kiện sẵn có:

1. Lấy `BP_HeroCharacter.m_airComboTarget` vào `m_airTarget`.
2. Target hợp lệ, còn sống, đang Falling và cách Hero không quá 300 cm.
3. Chạy Sequence: lưu gravity rồi giữ Hero; lưu gravity rồi giữ target.

Chỉ đổi ba dây exec; giữ nguyên data pins và các giá trị gameplay. `GA_Launcher` ghi target sau hit hợp lệ; Hero xóa target khi hết Falling. Không cần thêm biến đánh dấu launcher.

## Đối chiếu node trong Editor

Trong `GA_AirAttack > BeginAirHold`:

| Dây mới | Node đích |
| --- | --- |
| Function Entry: Then | Set `m_airTarget`: Execute |
| Branch `Distance <= 300`: True | Sequence: Execute |
| Sequence: Then 1 | Set gravity gốc của target: Execute |

`Sequence.Then0` vẫn nối vào phần lưu gravity của Hero. Các nhánh target không hợp lệ kết thúc function mà không dừng movement hoặc đổi gravity. Ability vẫn chạy air attack và áp dụng `State.AirComboUsed`.

Tên node trong snapshot: Entry `K2Node_FunctionEntry_0`; Set target `K2Node_VariableSet_4`; Branch khoảng cách `K2Node_IfThenElse_3`; Sequence `K2Node_ExecutionSequence_0`; lưu gravity target `K2Node_VariableSet_5`.

## Kiểm tra

Đã compile `GA_AirAttack` và fixture với `warnings_as_errors`; single-player PIE `Map_Startup` pass **18/18**, không có FAIL, có DONE. Run kết thúc lúc 22:53:16 ngày 2026-09-25 (UTC+7). Trước sửa, hai assertion “giữ nguyên vận tốc khi nhảy đánh” và “giữ gravity khi nhảy đánh” đều fail.

Kết quả runtime và log được ghi riêng trong [Diagnostics/launcher-only-air-hold-2026-09-25.json](Diagnostics/launcher-only-air-hold-2026-09-25.json). Đã save đúng `GA_AirAttack` và fixture mới, Stop PIE và gỡ actor test khỏi map; không Save All hoặc save map.

Fixture: `/Game/Tests/Combat/BP_LauncherOnlyAirHoldRegression`.

Source đầy đủ: [bp_launcher_only_air_hold_regression.dsl.txt](../Content/Tests/Combat/bp_launcher_only_air_hold_regression.dsl.txt).

Fixture dùng input GAS thật. Các ca hold/cleanup đầu tiên dựng cặp airborne và gán target để kiểm tra độc lập. Ca nhảy thường mô phỏng vận tốc nhảy 420 cm/s bằng `LaunchCharacter`, không dùng phím Space. Ca cuối dùng InputID 6 (E), sword trace thật và InputID 3 (LMB), không gán launcher target. Target của ca này được spawn cách 100 cm theo hướng mặt thực tế vì Hero bật `Use Controller Rotation Yaw`.

Các kiểm tra bao gồm: giữ cặp launcher; tag đã dùng và reset khi landing; bỏ input sớm; input đúng window vào Air_02; giữ vận tốc/gravity/quỹ đạo nhảy; kết thúc combo, interrupt và timeout 3 giây khôi phục gravity; launcher thật chọn target và nối air attack.

Để chạy lại: kéo đúng một fixture vào `Map_Startup`, PIE và không bấm input trong khoảng 30 giây. Lọc Output Log theo `[AIR ORIGIN TEST]`. Sau test, Stop PIE và xóa actor fixture khỏi level; không để fixture trong map demo.

Fixture cũ `BP_AirHoldRegression` và tài liệu `AIR_COMBO_FIX.md` lưu contract ngày 2026-09-20. Assertion cũ “air attack không có target vẫn giữ Hero” đã bị yêu cầu mới thay thế; dùng fixture mới cho regression này.

## Test bằng mắt

1. Đứng trước enemy, bấm E rồi LMB khi đã lên không: Hero và enemy khựng để đánh; bấm LMB trong combo window để nối Air_02.
2. Space rồi LMB: Hero vẫn lên và rơi theo quỹ đạo nhảy, không dừng giữa trời.
3. Kết thúc đòn hoặc ngắt montage: cặp đang giữ phải rơi trở lại. Tiếp đất rồi mới bắt đầu air combo tiếp theo.

## Rủi ro và giới hạn

- Chỉ giữ cặp khi target còn sống, đang Falling và trong 300 cm. Launcher trúng nhưng đánh tiếp quá muộn hoặc target ra khỏi phạm vi sẽ không treo Hero.
- Bản này chốt rule air hold; chưa thay clip, tốc độ montage, blend, camera hoặc hit stop. Cần test bằng mắt để đánh giá nhịp/pose.
- Kiểm tra trong single-player PIE, chưa chứng minh replication hoặc case target chết giữa hold.
- Launcher trong bố trí test này trúng ở 100 cm nhưng hụt ở 140 cm. Log còn cảnh báo `JumpToSectionName Launcher ... failed for Montage AM_Kwang_Launcher`; montage vẫn chạy, trace trúng và launch ở 100 cm. Cần kiểm tra section/tầm đánh khi polish launcher; bản sửa này không thay montage.
- Project vẫn có lỗi load `UIFloatingStatusBarClass` có sẵn trong log. Không coi kết quả regression này là toàn project hết lỗi.
- Backup function trước sửa và bản asset trên disk nằm ở `Saved/AirLauncherHoldFix/20260925/`. Bản disk không đại diện cho các chỉnh sửa chưa save trong Editor; dùng snapshot live để đối chiếu function.
