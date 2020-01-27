# Performance Numbers for r5embed

2019-03-28  Markku-Juhani O. Saarinen <mjos@pqshield.com>    

2020-01-27	Updated to new parameters and variant names.    

### Round5 Speed on Cortex M4 (STM32F407) clocked at 24 MHz

Numbers are given in 1000s of cycles:

*	**KeyGen**: Keypair generation, kilo cycles.
*	**Enc**: Encapsulation (KEM), kilo cycles.
*	**Dec**: Decapsulation (KEM), kilo cycles.
*	**KEX**: A full KeyGen-Enc-Dec exchange, kilo cycles.

	| **Variant**	| **KeyGen** | **Enc** |  **Dec** | **KEX** |
	|---------------|------------|---------|----------|---------|
	| R5ND_1CPA_5d	| 391	| 572	| 244	| 1207	|
	| R5ND_3CPA_5d	| 784	| 1081	| 396	| 2262	|
	| R5ND_5CPA_5d	| 1423	| 1948	| 688	| 4060	|
	| R5ND_1CCA_5d	| 364	| 573	| 731	| 1669	|
	| R5ND_3CCA_5d	| 784	| 1185	| 1493	| 3463	|
	| R5ND_5CCA_5d	| 1354	| 1987	| 2529	| 5871	|
	| R5ND_1CPA_0d	| 356	| 470	| 153	| 981	|
	| R5ND_3CPA_0d	| 1168	| 1560	| 549	| 3277	|
	| R5ND_5CPA_0d	| 1583	| 2131	| 713	| 4428	|
	| R5ND_1CCA_0d	| 486	| 732	| 903	| 2122	|
	| R5ND_3CCA_0d	| 796	| 1204	| 1463	| 3464	|
	| R5ND_5CCA_0d	| 1091	| 1646	| 1973	| 4712	|
	| R5N1_1CPA_0d	| 6705	| 4488	| 1280	| 12474	|
	| R5N1_3CPA_0d	| 10114	| 6749	| 1924	| 18788	|
	| R5N1_5CPA_0d	| 34831	| 19958	| 4460	| 59249	|
	| R5N1_1CCA_0d	| 4252	| 3615	| 4134	| 12002	|
	| R5N1_3CCA_0d	| 17317	| 11714	| 13202	| 42234	|
	| R5N1_5CCA_0d	| 23272	| 16042	| 17645	| 56960	|
	| R5ND_0CPA_2iot | 340	| 465	| 190	| 997	|
	| R5ND_1CPA_4longkey | 418	| 623 | 267	| 1310	|


### Round5 memory usage on ARMv7-M

All numbers are in bytes:

*	**KG**: Stack use by Key Generation, RAM bytes.
*	**Enc**: Stack use by Encapsulation, RAM bytes.
*	**Dec**: Stack use by Decapsulation, RAM bytes.
*	**PK**: Public Key size, bytes (transmitted).
*	**SK**: Secret Key size, bytes (stored).
*	**CT**: Ciphertext size, bytes (transmitted)
*	**SS**: Shared secret size, bytes (stored).
*	**Code**: Code size, excluding Keccak, in Flash (ROM) bytes.

	| **Variant**	| **KG** | **Enc** | **Dec** | **PK** | **SK** | **CT** | **SS** | **Code** |
	|---------------|-------|-------|-------|-------|-------|-------|-------|-------|
	| ND_1CPA_5d	| 3822	| 4821	| 2564	| 445	| 16	| 549	| 16	| 4974	|
	| ND_3CPA_5d	| 5550	| 6989	| 3548	| 780	| 24	| 859	| 24	| 6410	|
	| ND_5CPA_5d	| 6990	| 8733	| 4548	| 972	| 32	| 1063	| 32	| 4092	|
	| ND_1CCA_5d	| 3910	| 4981	| 5596	| 461	| 493	| 620	| 16	| 5326	|
	| ND_3CCA_5d	| 5598	| 7109	| 8052	| 780	| 828	| 934	| 24	| 6904	|
	| ND_5CCA_5d	| 7038	| 9029	| 10428	| 978	| 1042	| 1285	| 32	| 4722	|
	| ND_1CPA_0d	| 4478	| 5389	| 2308	| 634	| 16	| 682	| 16	| 2382	|
	| ND_3CPA_0d	| 6006	| 7501	| 4668	| 909	| 24	| 981	| 24	| 2438	|
	| ND_5CPA_0d	| 7494	| 9445	| 5924	| 1178	| 32	| 1274	| 32	| 2480	|
	| ND_1CCA_0d	| 4478	| 5581	| 6316	| 676	| 708	| 740	| 16	| 2770	|
	| ND_3CCA_0d	| 6110	| 7725	| 8836	| 983	| 1031	| 1103	| 24	| 2914	|
	| ND_5CCA_0d	| 8046	| 10237	| 11756	| 1349	| 1413	| 1509	| 32	| 2948	|
	| N1_1CPA_0d	| 18958	| 24389	| 17852	| 5214	| 16	| 5236	| 16	| 3136	|
	| N1_3CPA_0d	| 26606	| 35749	| 28084	| 8834	| 24	| 8866	| 24	| 3166	|
	| N1_5CPA_0d	| 40590	| 55181	| 46284	| 14264	| 32	| 14288	| 32	| 3274	|
	| N1_1CCA_0d	| 19502	| 25525	| 31316	| 5740	| 5772	| 5788	| 16	| 3310	|
	| N1_3CCA_0d	| 29870	| 39853	| 49564	| 9660	| 9708	| 9716	| 24	| 3678	|
	| N1_5CCA_0d	| 37406	| 52325	| 67028	| 14636	| 14700	| 14708	| 32	| 3574	|
	| ND_0CPA_2iot	| 3150	| 3845	| 2036	| 342	| 16	| 394	| 16	| 3442	|
	| ND_1CPA_4longkey	| 3790	| 4861 | 2660 | 453	| 24	| 563	| 24	| 5006	|

