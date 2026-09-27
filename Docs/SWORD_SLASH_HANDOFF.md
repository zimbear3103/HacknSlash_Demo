# Sword trail - checkpoint 2026-09-26

## Trạng thái
Đã triển khai, lưu asset và có ảnh PIE của một dải trail theo kiếm. Chưa hoàn tất verification. Goal budgetLimited, bộ đếm cuối trả 196362/100000 tokens; không đánh dấu complete.

## Thay đổi đã lưu
Trong /Game/GASDocumentation/Characters/Hero/Abilities/Attack/GroundCombo:
- P_SwordTrail_Single: duplicate P_Kwang_Primary_Trail, một AnimTrail emitter. Lifetime DistributionFloatConstant đặt 0.12s.
- M_SwordTrail_Single: material riêng additive, unlit, two-sided, UsedWithBeamTrails; emissive (4,2,0.3), opacity ParticleColor.A để fade theo tuổi. Không sửa material Kwang gốc.
- AM_Kwang_GroundCombo_Trail: duplicate montage, bỏ bốn GameplayCue.Shared.SwordSlash notifies; thêm bốn native AnimNotifyState_Trail, FX_weapon_base/FX_weapon_tip, recycle_spawned_systems=false. Giữ trace/combat windows, clips, sections.
- GA_MeleeAttack: chỉ đổi MontageToPlay sang montage mới. Graph trước/sau khớp khi thay reference đó; compile/save thành công. Asset đã dirty trước task, giữ mọi chỉnh sửa live sẵn có.
- /Game/Tests/Combat/BP_SwordTrailPreview: fixture đã lưu, actor tạm đã xóa khỏi Map_Startup. PIE đã dừng. Không save map. bThrottleCPUWhenNotForeground đã trả về true.

Không sửa trực tiếp NS_SwordSlash/GC_SwordSlash: đường melee hiện dùng native AnimTrail để lưu đường quét. Mesh arc gốc vẫn còn cho reference cũ. Không sửa damage, Poison, combo logic, sockets, source clips hoặc Git.

## Timing trail
| Section | Begin (s) | End (s) |
|---|---:|---:|
| Attack_01 | 0.182664 | 0.520902 |
| Attack_02 | 1.397691 | 1.683387 |
| Attack_03 | 2.652124 | 2.911549 |
| HeavyAttack | 3.913579 | 4.269056 |

## Barehand audit
AM_Kwang_BareHand dùng FullBody, MM_Attack_01/02/03. Melee dùng UpperBody, PrimaryAttack_A/B/C/D_Slow. Không chung attack clips; chung Kwang_Skeleton và ANS_CombatWindow. Barehand dùng ANS_BareHandTrace riêng, không có SwordSlash cue. Source clips đã đọc không có notifies. Chưa chạy runtime barehand regression sau sửa.

## Evidence
- Script asserts bốn Trail states, không còn cue cũ, combat notifies không đổi, original montage/barehand không đổi.
- PIE Map_Startup direct montage Attack_01/02/03/HeavyAttack và GAS PressInputID(3) đã tạo đúng một ParticleSystemComponent. Template đọc live là P_SwordTrail_Single.
- Attack_02/03 có 7 active particles ở sample khoảng 0.32s sau start section.
- Material Kwang cũ không thấy rõ vệt dù có particles/tessellation. Material riêng đã hiện một dải vàng theo kiếm.
- Saved/Screenshots/WindowsEditor/ScreenShot00005.png: Attack_03, material kiểm tra opacity constant 0.8.
- Saved/Screenshots/WindowsEditor/ScreenShot00006.png: HeavyAttack, material cuối opacity ParticleColor.A.
- Capsule đỏ là melee trace debug có sẵn, không phải nhiều trail. Native Trail spawnpoint/tessellation debug đã tắt lại.
- Blueprint/material compile qua Editor API thành công; không phải full C++ build/packaged-game proof.
- Commandlet exit1 do lỗi floating status bar/DDC sẵn có; riêng scripts báo SINGLE_TRAIL_BUILD_PASS và SWORD_TRAIL_MATERIAL_CREATED. Không gọi commandlet là clean pass.

## Còn phải làm
1. Test material cuối trên cả bốn section và combo chuyển section thực tế, hit/miss.
2. Runtime barehand: xác nhận không spawn trail.
3. Kết thúc swing, StopAnimMontage/interruption, chuyển barehand: xác nhận ngừng phát, component tự dọn, không nối vệt giữa đòn.
4. Effective lifetime sau reload/cook: T3D lúc tạo constant=0.12 nhưng cached RawDistribution table=0.35; chưa khẳng định lifetime runtime chính xác.
5. Visual polish: dải vàng đơn, fade theo tuổi; chưa có texture mask làm mềm mép.
6. Kiểm tra save/reference và git diff --check cuối. Không kết luận hoàn tất chỉ từ component count.

## Fixture
BeginPlay đặt timer PlayTrailTest sau 0.5s. PlayTrailTest đang direct-play HeavyAttack montage mới, timer FreezeTrailTest sau 0.32s. FreezeTrailTest pause, cast ParticleSystemComponent, log GetNumActiveParticles, gọi console Shot. Fixture lưu nhưng không đặt trong map.
Các biến m_case/m_section/m_sampleTime còn từ thử nghiệm đầu; graph cuối dùng literals. Editor background throttle gây sample chậm; tạm tắt khi test rồi phục hồi. Không save map với fixture.

## Diagnostics
Saved/SwordSlashAudit có trail-audit.json, single-trail-build.json, build_single_trail.py, build_trail_material.py, GA_MeleeAttack_before.txt, GA_MeleeAttack_before_disk.uasset. Scripts refuse overwrite assets đã tồn tại. T3D/log có thể cũ hơn asset cuối.

## Prompt để tiếp tục ở chat khác
Project F:\HacknSlash_Demo UE5.8.3. Đọc AGENTS.md và tài liệu này. User chốt một continuous trail theo lưỡi kiếm. Tiếp tục verification/polish trên P_SwordTrail_Single, M_SwordTrail_Single và AM_Kwang_GroundCombo_Trail đã nối GA_MeleeAttack. Có visual Attack_03 và HeavyAttack; lifecycle/barehand runtime chưa chứng minh. Giữ dirty assets; không regenerate graph sản phẩm, Save All, enable Python remote execution hoặc thay đổi Git. Goal cũ budgetLimited, cần ngân sách mới rõ ràng. Trước khi kết luận xong phải test barehand, interruption, cleanup và combo bằng material cuối.