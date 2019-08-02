# Performance Numbers for r5embed

2019-03-28  Markku-Juhani O. Saarinen <mjos@pqshield.com>    

2019-05-21	Updated to include numbers for R5SNEIK v1.1

### Round5 Speed on Cortex M4 (STM32F407) clocked at 24 MHz

Numbers are given in 1000s of cycles:

*	**KeyGen**: Keypair generation, kilo cycles.
*	**Enc**: Encapsulation (KEM) or Encryption (PKE), kilo cycles.
*	**Dec**: Decapsulation (KEM) or Decryption (PKE), kilo cycles.
*	**KEX**: A full KeyGen-Enc-Dec exchange, kilo cycles.

	| **Variant**	| **KeyGen** | **Enc** |  **Dec** | **KEX** |
	|---------------|------------|---------|----------|---------|
	| R5ND_1KEM_5d	| 391	| 573	| 244	| 1209	| 
	| R5ND_3KEM_5d	| 784	| 1083	| 398	| 2265	| 
	| R5ND_5KEM_5d	| 1427	| 1951	| 692	| 4071	| 
	| R5ND_1PKE_5d	| 365	| 599	| 752	| 1718	| 
	| R5ND_3PKE_5d	| 785	| 1212	| 1514	| 3512	| 
	| R5ND_5PKE_5d	| 1359	| 2017	| 2550	| 5927	| 
	| R5ND_1KEM_0d	| 357	| 470	| 153	| 982	| 
	| R5ND_3KEM_0d	| 1170	| 1563	| 551	| 3285	| 
	| R5ND_5KEM_0d	| 1588	| 2134	| 716	| 4439	| 
	| R5ND_1PKE_0d	| 487	| 758	| 923	| 2168	| 
	| R5ND_3PKE_0d	| 798	| 1233	| 1482	| 3513	| 
	| R5ND_5PKE_0d	| 1093	| 1678	| 1992	| 4763	| 
	| R5N1_1KEM_0d	| 6522	| 4328	| 1100	| 11952	| 
	| R5N1_3KEM_0d	| 9920	| 6578	| 1751	| 18250	| 
	| R5N1_5KEM_0d	| 34751	| 19845	| 4290	| 58886	| 
	| R5N1_1PKE_0d	| 4054	| 3399	| 3786	| 11240	| 
	| R5N1_3PKE_0d	| 17011	| 11160	| 12834	| 41007	| 
	| R5N1_5PKE_0d	| 23180	| 15644	| 17316	| 56141	| 
	| R5ND_0KEM_2iot	| 341	| 465	| 191	| 999	| 
	| R5ND_1KEM_4longkey	| 419	| 624	| 268	| 1313	| 

### Round5 memory usage on ARMv7-M

All numbers are in bytes:

*	**KeyGen**: Stack use by Key Generation, RAM bytes.
*	**Enc**: Stack use by Encapsulation (KEM) or Encryption (PKE), RAM bytes.
*	**Dec**: Stack use by Decapsulation (KEM) or Decryption (PKE), RAM bytes.
*	**PK**: Public Key size, Stored/Xfer bytes.
*	**SK**: Secret Key size, Stored/Xfer bytes.
*	**CT**: Ciphertext (expansion), Xfer bytes.
*	**Code**: Code size, excluding "common" components, Flash (ROM) bytes.

	| **Variant**	| **KeyGen** | **Enc** | **Dec** | **PK** | **SK** | **CT** | **Code** |
	|---------------|-------|-------|-------|-------|-------|-------|-------|
	| R5ND_1KEM_5d	| 4166	| 4845	| 2668	| 445	| 16	| 549	| 5316	| 
	| R5ND_3KEM_5d	| 5854	| 6949	| 3716	| 780	| 24	| 859	| 6622	| 
	| R5ND_5KEM_5d	| 7302	| 8717	| 4660	| 972	| 32	| 1063	| 4324	| 
	| R5ND_1PKE_5d	| 4262	| 5701	| 5700	| 461	| 493	| 652	| 5612	| 
	| R5ND_3PKE_5d	| 5902	| 8077	| 8076	| 780	| 828	| 966	| 7560	| 
	| R5ND_5PKE_5d	| 7342	| 10357	| 10356	| 978	| 1042	| 1317	| 5346	| 
	| R5ND_1KEM_0d	| 4814	| 5613	| 2356	| 634	| 16	| 682	| 2622	| 
	| R5ND_3KEM_0d	| 6326	| 7877	| 4716	| 909	| 24	| 981	| 2742	| 
	| R5ND_5KEM_0d	| 7806	| 9941	| 5972	| 1178	| 32	| 1274	| 2770	| 
	| R5ND_1PKE_0d	| 4814	| 6733	| 6732	| 676	| 708	| 772	| 3568	| 
	| R5ND_3PKE_0d	| 6430	| 9269	| 9268	| 983	| 1031	| 1135	| 3674	| 
	| R5ND_5PKE_0d	| 8366	| 12325	| 12324	| 1349	| 1413	| 1541	| 3664	| 
	| R5N1_1KEM_0d	| 19342	| 24389	| 17492	| 5214	| 16	| 5236	| 3166	| 
	| R5N1_3KEM_0d	| 26686	| 35477	| 27372	| 8834	| 24	| 8866	| 3214	| 
	| R5N1_5KEM_0d	| 40366	| 54605	| 45268	| 14264	| 32	| 14288	| 3330	| 
	| R5N1_1PKE_0d	| 19894	| 31381	| 31388	| 5740	| 5772	| 5820	| 3824	| 
	| R5N1_3PKE_0d	| 29950	| 49365	| 49364	| 9660	| 9708	| 9748	| 4184	| 
	| R5N1_5PKE_0d	| 37046	| 66501	| 66500	| 14636	| 14700	| 14740	| 4044	| 
	| R5ND_0KEM_2iot	| 3494	| 4005	| 2084	| 342	| 16	| 394	| 3772	| 
	| R5ND_1KEM_4longkey	| 4102	| 4845	| 2780	| 453	| 24	| 563	| 5354	| 

### R5SNEIK (v1.1) Speed on Cortex M4 (STM32F407), clocked at 24 MHz

Numbers are given in 1000s of cycles:

*	**KeyGen**: Keypair generation, kilo cycles.
*	**Enc**: Encapsulation (KEM) or Encryption (PKE), kilo cycles.
*	**Dec**: Decapsulation (KEM) or Decryption (PKE), kilo cycles.
*	**KEX**: A full KeyGen-Enc-Dec exchange, kilo cycles.

	| **Variant**	| **KeyGen** | **Enc** |  **Dec** | **KEX** |
	|---------------|------------|---------|----------|---------|
	| R5ND_1KEM_5d	| 278	| 418	| 164	| 861	| 
	| R5ND_3KEM_5d	| 586	| 816	| 272	| 1676	| 
	| R5ND_5KEM_5d	| 1204	| 1647	| 531	| 3382	| 
	| R5ND_1PKE_5d	| 251	| 421	| 549	| 1222	| 
	| R5ND_3PKE_5d	| 587	| 994	| 1239	| 2821	| 
	| R5ND_5PKE_5d	| 1141	| 1784	| 2240	| 5166	| 
	| R5ND_1KEM_0d	| 230	| 290	| 74	| 595	| 
	| R5ND_3KEM_0d	| 941	| 1251	| 382	| 2575	| 
	| R5ND_5KEM_0d	| 1350	| 1814	| 548	| 3712	| 
	| R5ND_1PKE_0d	| 362	| 544	| 673	| 1580	| 
	| R5ND_3PKE_0d	| 599	| 1014	| 1216	| 2830	| 
	| R5ND_5PKE_0d	| 869	| 1434	| 1710	| 4014	| 
	| R5N1_1KEM_0d	| 5858	| 3339	| 511	| 9708	| 
	| R5N1_3KEM_0d	| 9060	| 5119	| 791	| 14971	| 
	| R5N1_5KEM_0d	| 33126	| 17380	| 2341	| 52848	| 
	| R5N1_1PKE_0d	| 3524	| 2428	| 2681	| 8635	| 
	| R5N1_3PKE_0d	| 15770	| 10070	| 11020	| 36861	| 
	| R5N1_5PKE_0d	| 22039	| 14747	| 15850	| 52637	| 
	| R5ND_0KEM_2iot	| 239	| 331	| 120	| 692	| 
	| R5ND_1KEM_4longkey	| 288	| 442	| 182	| 913	|


### R5SNEIK (v1.1) Memory Usage on ARMv7-M

All numbers are in bytes:

*	**KeyGen**: Stack use by Key Generation, RAM bytes.
*	**Enc**: Stack use by Encapsulation (KEM) or Encryption (PKE), RAM bytes.
*	**Dec**: Stack use by Decapsulation (KEM) or Decryption (PKE), RAM bytes.
*	**PK**: Public Key size, Stored/Xfer bytes.
*	**SK**: Secret Key size, Stored/Xfer bytes.
*	**CT**: Ciphertext (expansion), Xfer bytes.
*	**Code**: Code size, excluding "common" components, Flash (ROM) bytes.

	| **Variant**	| **KeyGen** | **Enc** | **Dec** | **PK** | **SK** | **CT** | **Code** |
	|---------------|-------|-------|-------|-------|-------|-------|-------|
	| R5ND_1KEM_5d	| 3554	| 4481	| 2604	| 445	| 16	| 549	| 6588	|
	| R5ND_3KEM_5d	| 5298	| 6673	| 3716	| 780	| 24	| 859	| 7898	|
	| R5ND_5KEM_5d	| 6745	| 8433	| 4660	| 972	| 32	| 1063	| 5592	|
	| R5ND_1PKE_5d	| 3642	| 5329	| 5328	| 461	| 493	| 644	| 7366	|
	| R5ND_3PKE_5d	| 5346	| 7801	| 7800	| 780	| 828	| 958	| 8774	|
	| R5ND_5PKE_5d	| 6786	| 10073	| 10072	| 978	| 1042	| 1309	| 6544	|
	| R5ND_1KEM_0d	| 4194	| 5049	| 2080	| 634	| 16	| 682	| 3874	|
	| R5ND_3KEM_0d	| 5770	| 7593	| 4688	| 909	| 24	| 981	| 4018	|
	| R5ND_5KEM_0d	| 7250	| 9657	| 5944	| 1178	| 32	| 1274	| 4038	|
	| R5ND_1PKE_0d	| 4202	| 6305	| 6304	| 676	| 708	| 764	| 4770	|
	| R5ND_3PKE_0d	| 5874	| 8993	| 8992	| 983	| 1031	| 1127	| 4880	|
	| R5ND_5PKE_0d	| 7810	| 12049	| 12048	| 1349	| 1413	| 1533	| 4874	|
	| R5N1_1KEM_0d	| 18690	| 24049	| 17176	| 5214	| 16	| 5236	| 4434	|
	| R5N1_3KEM_0d	| 26106	| 35161	| 27128	| 8834	| 24	| 8866	| 4474	|
	| R5N1_5KEM_0d	| 39786	| 54289	| 45024	| 14264	| 32	| 14288	| 4594	|
	| R5N1_1PKE_0d	| 19242	| 31041	| 31048	| 5740	| 5772	| 5812	| 5026	|
	| R5N1_3PKE_0d	| 29362	| 49057	| 49056	| 9660	| 9708	| 9740	| 5382	|
	| R5N1_5PKE_0d	| 36458	| 66185	| 66184	| 14636	| 14700	| 14732	| 5242	|
	| R5ND_0KEM_2iot	| 2874	| 3505	| 1884	| 342	| 16	| 394	| 5036	|
	| R5ND_1KEM_4longkey	| 3554	| 4569	| 2780	| 453	| 24	| 563	| 6626	| 

