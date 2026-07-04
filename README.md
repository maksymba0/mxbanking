# MXBanking RE Lab

A deliberately vulnerable C++ banking app built to practice static & dynamic reverse engineering.

<img width="1367" height="911" alt="image" src="https://github.com/user-attachments/assets/a4617ed4-ddd6-43e7-b6bc-6f911cb9d3db" />

 <img width="1260" height="237" alt="image" src="https://github.com/user-attachments/assets/3b4676c8-b610-4f70-9f44-db282fc2254e" />


## The Hack (Visual Walkthrough)

1. **Trigger the error** – Entering a random key fires the `"Error. Invalid Key"` message.
<img width="726" height="202" alt="Screenshot 2026-06-30 203101" src="https://github.com/user-attachments/assets/1efbd078-822e-4dca-b3af-93235ea0794a" />

2. **Cross-reference the string** – Used x86dbg to find where the error message is referenced in the `symbols` section.
<img width="1081" height="876" alt="Screenshot 2026-06-30 200006" src="https://github.com/user-attachments/assets/0c303cee-8ba8-4d85-8b4b-3a4e0a643e10" />

3. **Locate the hardcoded check** – Scrolled to the `cmp` instruction comparing my input against `0x948B8C` (9735052).
<img width="1268" height="540" alt="Screenshot 2026-06-30 200101" src="https://github.com/user-attachments/assets/377c9a89-5bae-4080-ac87-607131732f20" />

4. **Patch it live** – Overwrote the `jne` with `NOP` instructions (0x90) to avoid the validation.
<img width="1082" height="245" alt="Screenshot 2026-06-30 200735" src="https://github.com/user-attachments/assets/631e20f7-b734-4715-867d-aee606af1f60" />


5. **Bypassed** – Entered `3`, the patch skipped the failure branch, and I connected straight to the bank's backend simulation.
<img width="1122" height="543" alt="Screenshot 2026-06-30 200758" src="https://github.com/user-attachments/assets/82df4ae0-6b57-43ab-9d4a-55407960091b" />


**Result:** Full authentication bypass in under a few minutes.
