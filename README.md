# jsontest

잠정적으로 C언어에서 사용가능한 JSON Library인 Jansson에 대한 사용 예제입니다. (조만간 언어간 상호 호환성을 검증할 예정입니다.)

호가데이터(B6)을 파싱해서 JSON객체에 담고 (각 호가 단계는 array로 처리), 다시 JSON객체에서 데이터를 읽어들이는 예제입니다.

Jansson 라이브러리외에 몇가지 저희회사 라이브러리가 있어야 빌드해서 동작시켜볼 수 있지만,
일단 소스코드만이라도 공유해드립니다.

Jansson library는 아래에서 다운로드 받으셔서 빌드하여 사용가능합니다.

http://www.digip.org/jansson/

==============================================================================================
1. 샘플데이터 전문 출력(마지막번째) :
dgubun[B6011] expcode[KR7005930003] seqno[00359] volume[000000324641] offer1[001445000] bid1[001444000] offerrem1[000000000005] bidrem1[000000000004] offer2[001446000] bid2[001443000] offerrem2[000000000012] bidrem2[000000000014] offer3[001447000] bid3[001442000] offerrem3[000000000019] bidrem3[000000000016] offer4[000000000] bid4[000000000] offerrem4[000000000000] bidrem4[000000000000] offer5[000000000] bid5[000000000] offerrem5[000000000000] bidrem5[000000000000] offer6[000000000] bid6[000000000] offerrem6[000000000000] bidrem6[000000000000] offer7[000000000] bid7[000000000] offerrem7[000000000000] bidrem7[000000000000] offer8[000000000] bid8[000000000] offerrem8[000000000000] bidrem8[000000000000] offer9[000000000] bid9[000000000] offerrem9[000000000000] bidrem9[000000000000] offer10[000000000] bid10[000000000] offerrem10[000000000000] bidrem10[000000000000] T_offerrem[000000000000] T_bidrem[000000000000] ptmofferrem[            ] ptmbidrem[            ] otmofferrem[000000000942] otmbidrem[000000000000] sid[20] boardid[프리보드] booltest1[1] booltest2[0] realtest[123456789.12] yeprice[001445000] yevolume[000000000009] bddirgb[0] filler[       ]


==============================================================================================
2. 생성된 JSON메시지 출력 :
{"hogaData": {"dgubun": "B6011", "expcode": "KR7005930003", "seqno": 359, "volume": 324641, "hoga": [{"offer": 1445000, "bid": 1444000, "offerrem": 5, "bidrem": 4}, {"offer": 1446000, "bid": 1443000, "offerrem": 12, "bidrem": 14}, {"offer": 1447000, "bid": 1442000, "offerrem": 19, "bidrem": 16}, {"offer": 0, "bid": 0, "offerrem": 0, "bidrem": 0}, {"offer": 0, "bid": 0, "offerrem": 0, "bidrem": 0}, {"offer": 0, "bid": 0, "offerrem": 0, "bidrem": 0}, {"offer": 0, "bid": 0, "offerrem": 0, "bidrem": 0}, {"offer": 0, "bid": 0, "offerrem": 0, "bidrem": 0}, {"offer": 0, "bid": 0, "offerrem": 0, "bidrem": 0}, {"offer": 0, "bid": 0, "offerrem": 0, "bidrem": 0}], "T_offerrem": 0, "T_bidrem": 0, "ptmofferrem": 0, "ptmbidrem": 0, "otmofferrem": 942, "otmbidrem": 0, "sid": "20", "booltest1": true, "booltest2": false, "realtest": 123456789.12, "boardid": "프리보드", "yeprice": 1445000, "yevolume": 9, "bddirgb": "0", "filler": null}}


==============================================================================================
3. JSON메시지로부터 추출된 값으로 설정한 구조체 출력 :
dgubun[B6011] expcode[KR7005930003] seqno[359] volume[324641] offer1[1445000] bid1[1444000] offerrem1[5] bidrem1[4] offer2[1446000] bid2[1443000] offerrem2[12] bidrem2[14] offer3[1447000] bid3[1442000] offerrem3[19] bidrem3[16] offer4[0] bid4[0] offerrem4[0] bidrem4[0] offer5[0] bid5[0] offerrem5[0] bidrem5[0] offer6[0] bid6[0] offerrem6[0] bidrem6[0] offer7[0] bid7[0] offerrem7[0] bidrem7[0] offer8[0] bid8[0] offerrem8[0] bidrem8[0] offer9[0] bid9[0] offerrem9[0] bidrem9[0] offer10[0] bid10[0] offerrem10[0] bidrem10[0] T_offerrem[0] T_bidrem[0] ptmofferrem[0] ptmbidrem[0] otmofferrem[942] otmbidrem[0] sid[20] boardid[프리보드] booltest1[1] booltest2[0] realtest[123456789.120000] yeprice[1445000] yevolume[9] bddirgb[0] filler[]

