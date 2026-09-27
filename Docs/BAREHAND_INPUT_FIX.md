# BareHand RMB checkpoint — 2026-09-21

## Phạm vi

Sửa nhánh nhận RMB theo checkpoint: chỉ nhận trong combo window của đòn 2, đóng window, in `BARE HEAVY ACCEPTED`. Không nối Charged Attack, không thêm damage hoặc animation finisher. RMB hợp lệ kết thúc chain ở Attack_02; không tính là combo attack thứ năm.

## Đã sửa

- `GA_BareHandHeavyAttack`: giữ tên asset và Ability2; đây là input forwarder, không phải attack độc lập.
- Required Tags: `State.CombatMode.BareHand`, `State.Attacking`.
- Blocked Tags: `State.Dead`, `State.Debuff.Stun`, `State.Airborne`.
- Xóa Ability Tags, Activation Owned Tags và Block Abilities With Tag của bản copy attack; Cost GE = None. Giữ graph gửi HeavyInput rồi EndAbility, không CommitAbility.
- `GA_BareHandAttack`: thêm `Event.Combat.HeavyInput` vào Event Tags của montage task.
- Giữ điều kiện index = 2 và window mở. Nhánh hợp lệ đóng window trước khi Print String; ngắt lời gọi light AdvanceCombo riêng ở nhánh RMB.
- Không thay đổi listener LMB, các dây damage/event payload, montage, Hero hoặc AnimBP.
- Hàm `AdvanceHeavyCombo` do người dùng tạo được giữ nguyên nhưng không gọi từ nhánh RMB.

## Bằng chứng kiểm tra

Fixture: `/Game/Tests/Combat/BP_BareHandInputRegression`, source đầy đủ ở `Content/Tests/Combat/bp_barehandinputregression.dsl.txt`.

PIE `Map_Startup` trước sửa, 09:15:51–09:15:59 UTC: 3 FAIL; light three-hit control PASS.

PIE sau sửa, 09:19:43–09:19:51 UTC: 4 PASS, 0 FAIL:

1. RMB khi idle không gửi event.
2. RMB được forward trong khi bare-hand attack đang active.
3. RMB ở đòn 1 không chiếm window; RMB ở window đòn 2 chiếm window trước LMB tiếp theo. Sequence quan sát: `Attack_01>Attack_02`; đúng một `BARE HEAVY ACCEPTED`.
4. LMB chain bình thường vẫn là `Attack_01>Attack_02>Attack_03`.

Lượt 09:18 bị loại khỏi bằng chứng pass vì Editor background throttle làm game chạy ở 3 FPS, control light combo cũng fail. Đã tạm tắt `bThrottleCPUWhenNotForeground` để test lại, rồi khôi phục `true`.

Hai ability và fixture đã compile/save. Actor fixture đã được gỡ khỏi map, PIE đã dừng; không save map và không commit Git.

## Chạy lại

1. Kéo `BP_BareHandInputRegression` vào Map_Startup, không cần save map.
2. Giữ Editor foreground, không thao tác input; chạy PIE ít nhất 10 giây.
3. Lọc Output Log bằng `[BARE INPUT TEST]`. Cần 4 PASS, không FAIL, sau đó DONE; có một `BARE HEAVY ACCEPTED`.
4. Dừng PIE và gỡ actor fixture. Asset test vẫn giữ để dùng lại.

Fixture tự thêm tag BareHand cho phiên PIE và dùng ASC PressInputID/ReleaseInputID. Đây không phải test phím F vật lý, animation bằng mắt, HP delta, stamina delta hoặc multiplayer. Trace/hit trên map không nằm trong assertion của fixture này.

## Bước tiếp theo đề xuất

Chuyển sang Day 5: GE_Poison nhỏ, apply từ MeleeHit đã hoạt động của BareHand light. Không triển khai Poison trong lượt sửa này. Mục tiêu 5 combo của Day 4 vẫn cần đánh giá riêng; checkpoint RMB chỉ in log không được tính là một attack combo hoàn thiện.
