## perkenalan
ini adalah repo untuk kontroller arduino yang digunakan untuk turntable di warak.
### pin definisi
berikut adalah wiring pin yang digunakan
1. pin dari arduino nano ke stepper driver

| arduino nano  | stepper driver |
| ------------- | ------------- |
| Gnd  | Gnd step- dir- enable- |
| 9  | step+ |
| 8  | dir+ |
| 7  | enable+ |

2. pin analog potensiometer

| arduino nano  | analog potensiometer |
| ------------- | ------------- |
| Gnd  | 1 |
| A0  | 2 |
| 5V  | 3 |

3. pin button

| arduino nano  | analog potensiometer |
| ------------- | ------------- |
| Gnd  | dir-input-gnd enable-input-gnd  |
| 11  | dir-input |
| 12  | enable-input |