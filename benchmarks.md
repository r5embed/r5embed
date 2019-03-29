# Performance Numbers for r5embed

2019-03-28  Markku-Juhani O. Saarinen <mjos@pqshield.com>


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

### R5SNEIK Speed on Cortex M4 (STM32F407), clocked at 24 MHz

Numbers are given in 1000s of cycles:

*	**KeyGen**: Keypair generation, kilo cycles.
*	**Enc**: Encapsulation (KEM) or Encryption (PKE), kilo cycles.
*	**Dec**: Decapsulation (KEM) or Decryption (PKE), kilo cycles.
*	**KEX**: A full KeyGen-Enc-Dec exchange, kilo cycles.

	| **Variant**	| **KeyGen** | **Enc** |  **Dec** | **KEX** |
	|---------------|------------|---------|----------|---------|
	| R5ND_1KEM_5d	| 280	| 419	| 164	| 864	| 
	| R5ND_3KEM_5d	| 589	| 821	| 274	| 1685	| 
	| R5ND_5KEM_5d	| 1212	| 1657	| 536	| 3406	| 
	| R5ND_1PKE_5d	| 252	| 397	| 525	| 1176	| 
	| R5ND_3PKE_5d	| 590	| 863	| 1109	| 2563	| 
	| R5ND_5PKE_5d	| 1148	| 1645	| 2103	| 4896	| 
	| R5ND_1KEM_0d	| 231	| 292	| 75	| 599	| 
	| R5ND_3KEM_0d	| 944	| 1258	| 385	| 2587	| 
	| R5ND_5KEM_0d	| 1358	| 1822	| 553	| 3734	| 
	| R5ND_1PKE_0d	| 363	| 512	| 641	| 1517	| 
	| R5ND_3PKE_0d	| 603	| 858	| 1061	| 2523	| 
	| R5ND_5PKE_0d	| 878	| 1258	| 1534	| 3670	| 
	| R5N1_1KEM_0d	| 5862	| 3357	| 517	| 9737	| 
	| R5N1_3KEM_0d	| 9087	| 5149	| 809	| 15045	| 
	| R5N1_5KEM_0d	| 33168	| 17449	| 2395	| 53013	| 
	| R5N1_1PKE_0d	| 3528	| 2171	| 2425	| 8125	| 
	| R5N1_3PKE_0d	| 15789	| 8759	| 9721	| 34269	| 
	| R5N1_5PKE_0d	| 22073	| 13065	| 14179	| 49318	| 
	| R5ND_0KEM_2iot	| 240	| 333	| 121	| 695	| 
	| R5ND_1KEM_4longkey	| 291	| 446	| 183	| 920	| 


### R5SNEIK Memory Usage on ARMv7-M

All numbers are in bytes:

*	**KeyGen**: Stack use by Key Generation, RAM bytes.
*	**Enc**: Stack use by Encapsulation (KEM) or Encryption (PKE), RAM bytes.
*	**Dec**: Stack use by Decapsulation (KEM) or Decryption (PKE), RAM bytes.
*	**PK**: Public Key size, Stored/Xfer bytes.
*	**SK**: Secret Key size, Stored/Xfer bytes.
*	**CT**: Ciphertext (expansion), Xfer bytes.
*	**Code**: Code size, excluding "common" components, Flash (ROM) bytes.

	| **Variant**	| **KeyGen** | **Enc** | **Dec** | **PK** | **SK** | **CT** | **Code** |
	| R5ND_1KEM_5d	| 3534	| 4461	| 2604	| 4892	| 
	| R5ND_3KEM_5d	| 5278	| 6653	| 3716	| 6202	| 
	| R5ND_5KEM_5d	| 6725	| 8517	| 4660	| 3896	| 
	| R5ND_1PKE_5d	| 3622	| 5309	| 5308	| 5612	| 
	| R5ND_3PKE_5d	| 5326	| 7781	| 7780	| 7020	| 
	| R5ND_5PKE_5d	| 6766	| 10053	| 10052	| 4790	| 
	| R5ND_1KEM_0d	| 4174	| 5029	| 2068	| 2178	| 
	| R5ND_3KEM_0d	| 5750	| 7573	| 4676	| 2322	| 
	| R5ND_5KEM_0d	| 7270	| 9637	| 5932	| 2342	| 
	| R5ND_1PKE_0d	| 4182	| 6285	| 6284	| 3016	| 
	| R5ND_3PKE_0d	| 5854	| 9013	| 8972	| 3126	| 
	| R5ND_5PKE_0d	| 7790	| 12029	| 12028	| 3120	| 
	| R5N1_1KEM_0d	| 18670	| 24029	| 17164	| 2738	| 
	| R5N1_3KEM_0d	| 26086	| 35141	| 27116	| 2778	| 
	| R5N1_5KEM_0d	| 39766	| 54269	| 45012	| 2898	| 
	| R5N1_1PKE_0d	| 19222	| 31021	| 31028	| 3272	| 
	| R5N1_3PKE_0d	| 29342	| 49037	| 49036	| 3628	| 
	| R5N1_5PKE_0d	| 36438	| 66165	| 66164	| 3488	| 
	| R5ND_0KEM_2iot	| 2854	| 3485	| 1884	| 3340	| 
	| R5ND_1KEM_4longkey	| 3534	| 4549	| 2780	| 4930	| 

