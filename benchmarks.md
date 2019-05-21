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
	| R5ND_1KEM_5d	| 282	| 423	| 166	| 872	|
	| R5ND_3KEM_5d	| 594	| 828	| 278	| 1702	|
	| R5ND_5KEM_5d	| 1224	| 1674	| 545	| 3444	|
	| R5ND_1PKE_5d	| 255	| 401	| 530	| 1188	|
	| R5ND_3PKE_5d	| 595	| 874	| 1121	| 2591	|
	| R5ND_5PKE_5d	| 1159	| 1665	| 2127	| 4952	|
	| R5ND_1KEM_0d	| 233	| 295	| 76	| 606	|
	| R5ND_3KEM_0d	| 950	| 1266	| 390	| 2608	|
	| R5ND_5KEM_0d	| 1370	| 1844	| 563	| 3778	|
	| R5ND_1PKE_0d	| 366	| 518	| 647	| 1532	|
	| R5ND_3PKE_0d	| 608	| 868	| 1073	| 2551	|
	| R5ND_5PKE_0d	| 888	| 1282	| 1561	| 3732	|
	| R5N1_1KEM_0d	| 5878	| 3381	| 532	| 9792	|
	| R5N1_3KEM_0d	| 9119	| 5191	| 843	| 15154	|
	| R5N1_5KEM_0d	| 33280	| 17621	| 2528	| 53430	|
	| R5N1_1PKE_0d	| 3540	| 2206	| 2463	| 8210	|
	| R5N1_3PKE_0d	| 15829	| 8834	| 9820	| 34484	|
	| R5N1_5PKE_0d	| 22141	| 13241	| 14391	| 49774	|
	| R5ND_0KEM_2iot	| 243	| 336	| 122	| 702	|
	| R5ND_1KEM_4longkey	| 294	| 451	| 186	| 931	|


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
	| R5ND_1KEM_5d	| 3546	| 4473	| 2604	| 445	| 16	| 549	| 4892	|
	| R5ND_3KEM_5d	| 5290	| 6665	| 3716	| 780	| 24	| 859	| 6202	|
	| R5ND_5KEM_5d	| 6737	| 8445	| 4660	| 972	| 32	| 1063	| 3896	|
	| R5ND_1PKE_5d	| 3634	| 5321	| 5320	| 461	| 493	| 644	| 5612	|
	| R5ND_3PKE_5d	| 5338	| 7793	| 7792	| 780	| 828	| 958	| 7020	|
	| R5ND_5PKE_5d	| 6778	| 10065	| 10064	| 978	| 1042	| 1309	| 4790	|
	| R5ND_1KEM_0d	| 4186	| 5041	| 2072	| 634	| 16	| 682	| 2178	|
	| R5ND_3KEM_0d	| 5762	| 7585	| 4680	| 909	| 24	| 981	| 2322	|
	| R5ND_5KEM_0d	| 7242	| 9749	| 5936	| 1178	| 32	| 1274	| 2342	|
	| R5ND_1PKE_0d	| 4194	| 6297	| 6296	| 676	| 708	| 764	| 3016	|
	| R5ND_3PKE_0d	| 5866	| 9013	| 8984	| 983	| 1031	| 1127	| 3126	|
	| R5ND_5PKE_0d	| 7802	| 12041	| 12040	| 1349	| 1413	| 1533	| 3120	|
	| R5N1_1KEM_0d	| 18682	| 24041	| 17168	| 5214	| 16	| 5236	| 2738	|
	| R5N1_3KEM_0d	| 26098	| 35153	| 27120	| 8834	| 24	| 8866	| 2778	|
	| R5N1_5KEM_0d	| 39778	| 54281	| 45016	| 14264	| 32	| 14288	| 2898	|
	| R5N1_1PKE_0d	| 19234	| 31033	| 31040	| 5740	| 5772	| 5812	| 3272	|
	| R5N1_3PKE_0d	| 29354	| 49049	| 49048	| 9660	| 9708	| 9740	| 3628	|
	| R5N1_5PKE_0d	| 36450	| 66177	| 66176	| 14636	| 14700	| 14732	| 3488	|
	| R5ND_0KEM_2iot	| 2866	| 3497	| 1884	| 342 | 16 | 394 | 3340 |
	| R5ND_1KEM_4longkey	| 3546	| 4561	| 2780	| 453 | 24 | 563 | 4930|


