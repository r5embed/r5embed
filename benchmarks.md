# Performance Numbers for r5embed

2019-03-28  Markku-Juhani O. Saarinen <mjos@pqshield.com>

2020-04-06  Updated to TupleHash version.


### Round5 Speed on Cortex M4 (STM32F407) clocked at 24 MHz

Numbers are given in 1000s of cycles:

| **Variant**   | **KG** | **Enc** |  **Dec** | **KEX** |
|---------------|--------|---------|----------|---------|
| R5ND_1CPA_5d  | 425  	| 607   | 247   | 1280  |
| R5ND_3CPA_5d  | 839   | 1136  | 400   | 2376  |
| R5ND_5CPA_5d  | 1455  | 1976  | 697   | 4129  |
| R5ND_1CCA_5d  | 384   | 593   | 755   | 1734  |
| R5ND_3CCA_5d  | 840   | 1253  | 1567  | 3661  |
| R5ND_5CCA_5d  | 1386  | 2011  | 2563  | 5961  |
| R5ND_1CPA_0d  | 360   | 474   | 155   | 990   |
| R5ND_3CPA_0d  | 1223  | 1615  | 555   | 3393  |
| R5ND_5CPA_0d  | 1593  | 2141  | 719   | 4455  |
| R5ND_1CCA_0d  | 504   | 750   | 926   | 2181  |
| R5ND_3CCA_0d  | 832   | 1241  | 1505  | 3579  |
| R5ND_5CCA_0d  | 1161  | 1714  | 2047  | 4923  |
| R5N1_1CPA_0d  | 6625  | 4488  | 1209  | 12323 |
| R5N1_3CPA_0d  | 9935  | 7063  | 1849  | 18849 |
| R5N1_5CPA_0d  | 34833 | 20891 | 4455  | 60181 |
| R5N1_1CCA_0d  | 4166  | 3723  | 4051  | 11942 |
| R5N1_3CCA_0d  | 17094 | 11986 | 13572 | 42654 |
| R5N1_5CCA_0d  | 23206 | 16681 | 17949 | 57837 |
| R5ND_0CPA_2iot    | 393   | 517   | 195   | 1106  |
| R5ND_1CPA_4longkey    | 423   | 628   | 271   | 1324  |
*   **KG**: Keypair generation, kilo cycles.
*   **Enc**: Encapsulation (KEM), kilo cycles.
*   **Dec**: Decapsulation (KEM), kilo cycles.
*   **KEX**: A full KeyGen-Enc-Dec exchange, kilo cycles.


### Round5 memory usage on ARMv7-M

All numbers are in bytes:

| **Variant**   | **KG** | **Enc** | **Dec** | **PK** | **SK** | **CT** | **SS** | **Code** |
|---------------|-------|-------|-------|-------|-------|-------|-------|-------|
| R5ND_1CPA_5d  | 3862  | 4317  | 2124  | 445   | 16    | 549   | 16    | 5894  |
| R5ND_3CPA_5d  | 5598  | 6173  | 2708  | 780   | 24    | 859   | 24    | 7332  |
| R5ND_5CPA_5d  | 7038  | 7717  | 3468  | 972   | 32    | 1063  | 32    | 4828  |
| R5ND_1CCA_5d  | 3958  | 4405  | 5028  | 461   | 493   | 620   | 16    | 6248  |
| R5ND_3CCA_5d  | 5638  | 6229  | 7164  | 780   | 828   | 934   | 24    | 7788  |
| R5ND_5CCA_5d  | 7078  | 7781  | 9068  | 978   | 1042  | 1285  | 32    | 5412  |
| R5ND_1CPA_0d  | 4526  | 4765  | 1716  | 634   | 16    | 682   | 16    | 3054  |
| R5ND_3CPA_0d  | 6054  | 6565  | 3676  | 909   | 24    | 981   | 24    | 3114  |
| R5ND_5CPA_0d  | 7542  | 8205  | 4628  | 1178  | 32    | 1274  | 32    | 3160  |
| R5ND_1CCA_0d  | 4518  | 4877  | 5620  | 676   | 708   | 740   | 16    | 3440  |
| R5ND_3CCA_0d  | 6150  | 6669  | 7772  | 983   | 1031  | 1103  | 24    | 3554  |
| R5ND_5CCA_0d  | 8078  | 8757  | 10268 | 1349  | 1413  | 1509  | 32    | 3586  |
| R5N1_1CPA_0d  | 19286 | 19501 | 12996 | 5214  | 16    | 5236  | 16    | 3796  |
| R5N1_3CPA_0d  | 26950 | 27221 | 19556 | 8834  | 24    | 8866  | 24    | 3804  |
| R5N1_5CPA_0d  | 40934 | 41213 | 32324 | 14264 | 32    | 14288 | 32    | 3910  |
| R5N1_1CCA_0d  | 19878 | 20109 | 25900 | 5740  | 5772  | 5788  | 16    | 3892  |
| R5N1_3CCA_0d  | 30206 | 30485 | 40204 | 9660  | 9708  | 9716  | 24    | 4228  |
| R5N1_5CCA_0d  | 37638 | 37933 | 52644 | 14636 | 14700 | 14708 | 32    | 4164  |
| R5ND_0CPA_2iot    | 3198  | 3501  | 1740  | 342   | 16    | 394   | 16    | 3618  |
| R5ND_1CPA_4longkey    | 3830  | 4357  | 2180  | 453   | 24    | 563   | 24    | 5764  |


*   **KG**: Stack use by Key Generation, RAM bytes.
*   **Enc**: Stack use by Encapsulation, RAM bytes.
*   **Dec**: Stack use by Decapsulation, RAM bytes.
*   **PK**: Public Key size, bytes (transmitted).
*   **SK**: Secret Key size, bytes (stored).
*   **CT**: Ciphertext size, bytes (transmitted)
*   **SS**: Shared secret size, bytes (stored).
*   **Code**: Code size, excluding Keccak, in Flash (ROM) bytes.

