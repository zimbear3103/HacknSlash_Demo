# Air combo hold fix — 2026-09-20

> Contract air hold đã đổi ngày 2026-09-25: nhảy đánh không có launcher target phải rơi bình thường. Assertion số 8 và fixture trong tài liệu này chỉ ghi lại hành vi cũ. Dùng [Launcher-only air hold](AIR_LAUNCHER_ONLY_HOLD.md) và `BP_LauncherOnlyAirHoldRegression` cho kiểm tra hiện tại.

## Kết quả

Đã sửa và lưu GA_AirAttack, GA_Launcher và BP_HeroCharacter. Ba Blueprint compile thành công với warnings_as_errors. Kiểm tra runtime trong PIE Map_Startup bằng fixture riêng: 10/10 assertion pass. git diff --check pass.

## Thay đổi

- GA_AirAttack / BeginAirHold: m_targetHeld được set true sau khi gravity của enemy về 0, để ReleaseAirHold khôi phục gravity.
- GA_AirAttack / EventGraph: thêm State.AirComboUsed trên Hero sau Commit và Cast thành công, trước BeginAirHold.
- GA_AirAttack: Cast Failed nối EndAbility; WaitDelay 3 giây nối EndAbility. Sequence khởi tạo listener, theo dõi mất State.Airborne, timeout, rồi montage.
- BP_HeroCharacter: khi hết Falling, kiểm tra và remove State.AirComboUsed. State.Airborne và clear target giữ flow hiện tại.
- GA_Launcher: thêm Is Valid bằng exec trước IsAlive trong OnLaunchTarget và OnLaunchHero.
- Không thay đổi animation, timing combo window, damage, cost hay binding E/RMB/LMB.

## Bằng chứng trước và sau

Fixture BP_AirHoldRegression dùng PressInputID/ReleaseInputID thật trên ASC. Nó tạo platform và minion riêng trong PIE, spawn controller cho minion, đặt Hero/target airborne để kiểm tra air hold độc lập với launcher trace.

Trước sửa: 1/4 assertion pass. Giữ hai nhân vật pass; thiếu State.AirComboUsed, không restore gravity của target, và reactivation trước landing đều fail.
Sau sửa: cùng bốn assertion pass, cộng sáu kiểm tra mở rộng bên dưới.

1. Hero và target có gravity 0 trong air attack.
2. State.AirComboUsed được thêm.
3. Bấm LMB sớm ngoài window không kéo dài combo; cả hai gravity về 1.
4. Bấm tiếp trước landing không kích hoạt air ability lại.
5. Hạ đất thật trên platform test xóa tag đã dùng.
6. Bấm đúng window chuyển montage sang Air_02 thật.
7. Kết thúc hai đòn khôi phục gravity cả hai.
8. Air attack không có target vẫn giữ Hero.
9. Ngắt montage khôi phục gravity.
10. Làm chậm montage instance trong fixture: timeout 3 giây vẫn kết thúc ability và khôi phục gravity.

Log: Diagnostics/air-hold-regression-2026-09-20.json.
Source đầy đủ của fixture: ../Content/Tests/Combat/bp_airholdregression.dsl.txt.
Asset test: /Game/Tests/Combat/BP_AirHoldRegression.

## Chạy lại

- Mở Map_Startup và kéo đúng một BP_AirHoldRegression vào level.
- PIE, không tự bấm input trong lúc fixture chạy (~22 giây).
- Lọc Output Log theo [AIR TEST], phải có 10 PASS và DONE, không có FAIL.
- Stop PIE và xóa actor test khỏi level. Actor tạo platform/minion chỉ trong PIE.
- Fixture sẽ dịch chuyển Hero để test; không để actor này trong map demo.

Phiên kiểm tra đã Stop PIE và gỡ actor test khỏi Map_Startup. Chỉ save ba Blueprint sửa và asset fixture, không Save All hoặc save map.

## Backup

Saved/AirComboFix/20260920-004906/ chứa bản uasset trước sửa trên disk và bản trạng thái Editor trước sửa; có snapshot node trước/sau để đối chiếu. Giữ backup ngoài Content để tránh trùng package.

## Giới hạn và bước tiếp theo

Đây là kiểm tra input/montage/air hold/cleanup trong single-player PIE. Chưa xác nhận damage từng hit và visual alignment xuyên suốt chuỗi E → LMB → LMB trên enemy thật, chưa test multiplayer. Không tính là hoàn tất visual polish Day 3.

Tiếp theo: test E → LMB → LMB ở khoảng cách 100–160 cm; kiểm tra sword trace và HP từng đòn; sau đó cho Hero quay yaw về target một lần khi BeginAirHold nhận target hợp lệ. Giữ vị trí capsule, không teleport sát enemy.
