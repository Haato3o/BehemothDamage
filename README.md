# Behemoth Damage

This Monster Hunter World plugin patches the in-game damage function so it ignores the comparision to see if the monster is Behemoth or not, letting all monsters have the same damage text style as Behemoth.

## How it works

In short, the game has two different functions to draw damage on the player's screen, one for Behemoth and one for everything else. All this plugin does is `nop` the `jne` that checks whether the monster that you dealt damage to is Behemoth or not.

```nasm

; start of function
sub rsp,68
; rcx is our monster pointer, 0x12280 is the offset for its game Id
; 0x0F is Behemoth's game Id
cmp dword ptr [rcx+0x00012280],0x0F
jne MonsterHunterWorld.exe+0x1CE16D6 ; Jumps to normal damage function if monster Id is different from Behemoth's

```