#include "kplpdefine.h"
#include "kplpmacros.h"
#include "kplpdatetime.h"
#include "kplpstringmani.h"

#include <stdio.h>
#include <jansson.h>

#define TEST_CNT	1000000

#define INSERT_STRING	1
#define INSERT_INTEGER	2
#define INSERT_REAL		3
#define INSERT_BOOLEAN	4
#define INSERT_NULL		7

#define B6011_DATA_1 "B6011KR700593000300359000000324641001445000001444000000000000005000000000004001446000001443000000000000012000000000014001447000001442000000000000019000000000016000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000                        00000000094200000000000020프리보드10123456789.120014450000000000000090       "

#define B6011_DATA_2 "B6011KR700593000300359000000324641001445000001444000000000000005000000000004001446000001443000000000000012000000000014001447000001442000000000000019000000000016000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000                        00000000094200000000000020프리보드10987654321.120014450000000000000090       "

#define B6011_DATA_3 "B6011KR700006000300359000000324641001445000001444000000000000005000000000004001446000001443000000000000012000000000014001447000001442000000000000019000000000016000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000                        00000000094200000000000020프리보드10123451234.120014450000000000000090       "

typedef struct _B6011_HOGA {
	char offer			[ 9];	// 매도호가
	char bid			[ 9];	// 매수호가
	char offerrem		[12];	// 매도호가잔량
	char bidrem			[12];	// 매수호가잔량
} B6011_HOGA;

typedef struct _B6011 {
	char dgubun			[ 5];	// 구분코드
	char expcode		[12];	// 종목코드
	char seqno			[ 5];	// 종목일련번호
	char volume			[12];	// 체결수량
	B6011_HOGA hoga		[10];	// 호가 및 호가잔량
	char T_offerrem		[12];	// 10단계호가매도총잔량
	char T_bidrem		[12];	// 10단계호가매수총잔량
	char ptmofferrem	[12];	// 장개시전시간외매도총호가잔량
	char ptmbidrem		[12];	// 장개시전시간외매수총호가잔량
	char otmofferrem	[12];	// 장종료후시간외매도총호가잔량
	char otmbidrem		[12];	// 장종료후시간외매수총호가잔량
	char sid			[ 2];	// 세션ID
	char boardid		[12];	// 보드ID
	char booltest1		[ 1];	// 테스트필드1
	char booltest2		[ 1];	// 테스트필드2
	char realtest		[12];	// 테스트필드3
	char yeprice		[ 9];	// 예상체결가격
	char yevolume		[12];	// 예상체결수량
	char bddirgb		[ 1];	// 경쟁대량 방향구분
	char filler			[ 7];	// FILLER
} B6011;


typedef struct _ORDER_HOGA {
	long offer;
	long bid;
	long offerrem;
	long bidrem;
} ORDER_HOGA;

typedef struct _ORDER {
	char	dgubun		[ 5+1]	;	// 구분코드
	char	expcode		[12+1]	;	// 종목코드
	int		seqno				;	// 종목일련번호
	long	volume				;	// 체결수량
	ORDER_HOGA hoga		[10+1]	;	// 호가 및 호가잔량
	long	T_offerrem			;	// 10단계호가매도총잔량
	long	T_bidrem			;	// 10단계호가매수총잔량
	long	ptmofferrem			;	// 장개시전시간외매도총호가잔량
	long	ptmbidrem			;	// 장개시전시간외매수총호가잔량
	long	otmofferrem			;	// 장종료후시간외매도총호가잔량
	long	otmbidrem			;	// 장종료후시간외매수총호가잔량
	char	sid			[ 2+1]	;	// 세션ID
	char	boardid		[12+1]	;	// 보드ID
	int		booltest1			;	// 테스트필드1
	int		booltest2			;	// 테스트필드2
	double	realtest			;	// 테스트필드3
	long	yeprice				;	// 예상체결가격
	long	yevolume			;	// 예상체결수량
	char	bddirgb		[ 1+1]	;	// 경쟁대량 방향구분
	char	filler		[ 7+1]	;	// FILLER
} ORDER;


int insert(json_t *pstRoot, const char *sKey, const char *sValue, int nLen, int nType)
{
	json_t *pstValue;
	char szValue[1024];

	memset(szValue, 0x00, sizeof(szValue));
	memcpy(szValue, sValue, nLen);

	switch(nType) {
		case INSERT_STRING:
			pstValue = json_string(szValue);
			break;
		case INSERT_INTEGER:
			pstValue = json_integer(kplpAToLong(szValue, nLen));
			break;
		case INSERT_REAL:
			pstValue = json_real(kplpAToDouble(szValue, nLen));
			break;
		case INSERT_BOOLEAN:
			pstValue = json_boolean(kplpAToLong(szValue, nLen));
			break;
		case INSERT_NULL:
			pstValue = json_null();
			break;
		default:
			return -1;
	}

	json_object_set(pstRoot, sKey, pstValue);
	json_decref(pstValue);
}

int main(int argc, char *argv[])
{
#if 1
	json_t *pstRootRoot; 
#endif
	json_t *pstRoot;
	json_t *pstArray;
	json_t *pstValue;
	json_t *pstHoga;

	B6011 stB6011;
	ORDER stOrder;
	
	char szData[10240];
	char *szString;
	int rtn, i, nSize;
	long lStart, lEnd, lLoop, lTestCnt;

	if(argc > 1) {
		lTestCnt = kplpAToLong(argv[1], strlen(argv[1]));
	}
	else {
		lTestCnt = TEST_CNT;
	}

	memset(&stB6011, 0x20, sizeof(stB6011));
	switch((lTestCnt - 1) % 3) {
		case 0:
			memcpy(&stB6011, B6011_DATA_1, strlen(B6011_DATA_1));
			break;
		case 1:
			memcpy(&stB6011, B6011_DATA_2, strlen(B6011_DATA_2));
			break;
		case 2:
		default:
			memcpy(&stB6011, B6011_DATA_3, strlen(B6011_DATA_3));
			break;
	}

	printf("==============================================================================================\n");
	printf("1. 샘플데이터 전문 출력(마지막번째) :\n");
	printf("dgubun[%.*s] expcode[%.*s] seqno[%.*s] volume[%.*s] \
offer1[%.*s] bid1[%.*s] offerrem1[%.*s] bidrem1[%.*s] \
offer2[%.*s] bid2[%.*s] offerrem2[%.*s] bidrem2[%.*s] \
offer3[%.*s] bid3[%.*s] offerrem3[%.*s] bidrem3[%.*s] \
offer4[%.*s] bid4[%.*s] offerrem4[%.*s] bidrem4[%.*s] \
offer5[%.*s] bid5[%.*s] offerrem5[%.*s] bidrem5[%.*s] \
offer6[%.*s] bid6[%.*s] offerrem6[%.*s] bidrem6[%.*s] \
offer7[%.*s] bid7[%.*s] offerrem7[%.*s] bidrem7[%.*s] \
offer8[%.*s] bid8[%.*s] offerrem8[%.*s] bidrem8[%.*s] \
offer9[%.*s] bid9[%.*s] offerrem9[%.*s] bidrem9[%.*s] \
offer10[%.*s] bid10[%.*s] offerrem10[%.*s] bidrem10[%.*s] \
T_offerrem[%.*s] T_bidrem[%.*s] ptmofferrem[%.*s] ptmbidrem[%.*s] \
otmofferrem[%.*s] otmbidrem[%.*s] sid[%.*s] boardid[%.*s] \
booltest1[%.*s] booltest2[%.*s] realtest[%.*s] \
yeprice[%.*s] yevolume[%.*s] bddirgb[%.*s] filler[%.*s]\n\n\n", 
			sizeof(stB6011.dgubun			), stB6011.dgubun			,
			sizeof(stB6011.expcode			), stB6011.expcode			,
			sizeof(stB6011.seqno			), stB6011.seqno			,
			sizeof(stB6011.volume			), stB6011.volume			,
			sizeof(stB6011.hoga[0].offer	), stB6011.hoga[0].offer	,
			sizeof(stB6011.hoga[0].bid		), stB6011.hoga[0].bid		,
			sizeof(stB6011.hoga[0].offerrem	), stB6011.hoga[0].offerrem	,
			sizeof(stB6011.hoga[0].bidrem	), stB6011.hoga[0].bidrem	,
			sizeof(stB6011.hoga[1].offer	), stB6011.hoga[1].offer	,
			sizeof(stB6011.hoga[1].bid		), stB6011.hoga[1].bid		,
			sizeof(stB6011.hoga[1].offerrem	), stB6011.hoga[1].offerrem	,
			sizeof(stB6011.hoga[1].bidrem	), stB6011.hoga[1].bidrem	,
			sizeof(stB6011.hoga[2].offer	), stB6011.hoga[2].offer	,
			sizeof(stB6011.hoga[2].bid		), stB6011.hoga[2].bid		,
			sizeof(stB6011.hoga[2].offerrem	), stB6011.hoga[2].offerrem	,
			sizeof(stB6011.hoga[2].bidrem	), stB6011.hoga[2].bidrem	,
			sizeof(stB6011.hoga[3].offer	), stB6011.hoga[3].offer	,
			sizeof(stB6011.hoga[3].bid		), stB6011.hoga[3].bid		,
			sizeof(stB6011.hoga[3].offerrem	), stB6011.hoga[3].offerrem	,
			sizeof(stB6011.hoga[3].bidrem	), stB6011.hoga[3].bidrem	,
			sizeof(stB6011.hoga[4].offer	), stB6011.hoga[4].offer	,
			sizeof(stB6011.hoga[4].bid		), stB6011.hoga[4].bid		,
			sizeof(stB6011.hoga[4].offerrem	), stB6011.hoga[4].offerrem	,
			sizeof(stB6011.hoga[4].bidrem	), stB6011.hoga[4].bidrem	,
			sizeof(stB6011.hoga[5].offer	), stB6011.hoga[5].offer	,
			sizeof(stB6011.hoga[5].bid		), stB6011.hoga[5].bid		,
			sizeof(stB6011.hoga[5].offerrem	), stB6011.hoga[5].offerrem	,
			sizeof(stB6011.hoga[5].bidrem	), stB6011.hoga[5].bidrem	,
			sizeof(stB6011.hoga[6].offer	), stB6011.hoga[6].offer	,
			sizeof(stB6011.hoga[6].bid		), stB6011.hoga[6].bid		,
			sizeof(stB6011.hoga[6].offerrem	), stB6011.hoga[6].offerrem	,
			sizeof(stB6011.hoga[6].bidrem	), stB6011.hoga[6].bidrem	,
			sizeof(stB6011.hoga[7].offer	), stB6011.hoga[7].offer	,
			sizeof(stB6011.hoga[7].bid		), stB6011.hoga[7].bid		,
			sizeof(stB6011.hoga[7].offerrem	), stB6011.hoga[7].offerrem	,
			sizeof(stB6011.hoga[7].bidrem	), stB6011.hoga[7].bidrem	,
			sizeof(stB6011.hoga[8].offer	), stB6011.hoga[8].offer	,
			sizeof(stB6011.hoga[8].bid		), stB6011.hoga[8].bid		,
			sizeof(stB6011.hoga[8].offerrem	), stB6011.hoga[8].offerrem	,
			sizeof(stB6011.hoga[8].bidrem	), stB6011.hoga[8].bidrem	,
			sizeof(stB6011.hoga[9].offer	), stB6011.hoga[9].offer	,
			sizeof(stB6011.hoga[9].bid		), stB6011.hoga[9].bid		,
			sizeof(stB6011.hoga[9].offerrem	), stB6011.hoga[9].offerrem	,
			sizeof(stB6011.hoga[9].bidrem	), stB6011.hoga[9].bidrem	,
			sizeof(stB6011.T_offerrem		), stB6011.T_offerrem		,
			sizeof(stB6011.T_bidrem			), stB6011.T_bidrem			,	    
			sizeof(stB6011.ptmofferrem		), stB6011.ptmofferrem		,
			sizeof(stB6011.ptmbidrem		), stB6011.ptmbidrem		,
			sizeof(stB6011.otmofferrem		), stB6011.otmofferrem		,
			sizeof(stB6011.otmbidrem		), stB6011.otmbidrem		,
			sizeof(stB6011.sid				), stB6011.sid				,     
			sizeof(stB6011.boardid			), stB6011.boardid			,    
			sizeof(stB6011.booltest1		), stB6011.booltest1		,
			sizeof(stB6011.booltest2		), stB6011.booltest2		,
			sizeof(stB6011.realtest			), stB6011.realtest			,    
			sizeof(stB6011.yeprice			), stB6011.yeprice			,     
			sizeof(stB6011.yevolume			), stB6011.yevolume			,    
			sizeof(stB6011.bddirgb			), stB6011.bddirgb			,
			sizeof(stB6011.filler			), stB6011.filler			);

	lStart = kplpGetMonotonicTime(NULL, KPLP_TIME_NS);

	for(lLoop = 0; lLoop < lTestCnt; lLoop++) {
		memset(&stB6011, 0x00, sizeof(stB6011));
		switch(lLoop % 3) {
			case 0:
				memcpy(&stB6011, B6011_DATA_1, strlen(B6011_DATA_1));
				break;
			case 1:
				memcpy(&stB6011, B6011_DATA_2, strlen(B6011_DATA_2));
				break;
			case 2:
			default:
				memcpy(&stB6011, B6011_DATA_3, strlen(B6011_DATA_3));
				break;
		}

		// 호가 전문으로부터 json메시지 생성
		pstRoot = json_object();
		pstArray = json_array();

		insert(pstRoot, "dgubun"		, stB6011.dgubun			, sizeof(stB6011.dgubun				), INSERT_STRING	);
		insert(pstRoot, "expcode"		, stB6011.expcode			, sizeof(stB6011.expcode			), INSERT_STRING	);
		insert(pstRoot, "seqno"			, stB6011.seqno				, sizeof(stB6011.seqno				), INSERT_INTEGER	);
		insert(pstRoot, "volume"		, stB6011.volume			, sizeof(stB6011.volume				), INSERT_INTEGER   );

		for(i = 0; i < 10; i++) {
			pstHoga = json_object();
			insert(pstHoga, "offer"			, stB6011.hoga[i].offer		, sizeof(stB6011.hoga[i].offer		), INSERT_INTEGER	);
			insert(pstHoga, "bid"			, stB6011.hoga[i].bid		, sizeof(stB6011.hoga[i].bid		), INSERT_INTEGER	);
			insert(pstHoga, "offerrem"		, stB6011.hoga[i].offerrem	, sizeof(stB6011.hoga[i].offerrem	), INSERT_INTEGER	);
			insert(pstHoga, "bidrem"		, stB6011.hoga[i].bidrem	, sizeof(stB6011.hoga[i].bidrem		), INSERT_INTEGER	);
			json_array_append(pstArray, pstHoga);
			json_decref(pstHoga);
		}
		json_object_set(pstRoot, "hoga", pstArray);
		json_decref(pstArray);

		insert(pstRoot, "T_offerrem"	, stB6011.T_offerrem		, sizeof(stB6011.T_offerrem			), INSERT_INTEGER   );
		insert(pstRoot, "T_bidrem"		, stB6011.T_bidrem			, sizeof(stB6011.T_bidrem			), INSERT_INTEGER   );
		insert(pstRoot, "ptmofferrem"	, stB6011.ptmofferrem		, sizeof(stB6011.ptmofferrem		), INSERT_INTEGER   );
		insert(pstRoot, "ptmbidrem"		, stB6011.ptmbidrem			, sizeof(stB6011.ptmbidrem			), INSERT_INTEGER   );
		insert(pstRoot, "otmofferrem"	, stB6011.otmofferrem		, sizeof(stB6011.otmofferrem		), INSERT_INTEGER   );
		insert(pstRoot, "otmbidrem"		, stB6011.otmbidrem			, sizeof(stB6011.otmbidrem			), INSERT_INTEGER   );
		insert(pstRoot, "sid"			, stB6011.sid				, sizeof(stB6011.sid				), INSERT_STRING	);
		insert(pstRoot, "booltest1"		, stB6011.booltest1			, sizeof(stB6011.booltest1			), INSERT_BOOLEAN	);
		insert(pstRoot, "booltest2"		, stB6011.booltest2			, sizeof(stB6011.booltest2			), INSERT_BOOLEAN	);
		insert(pstRoot, "realtest"		, stB6011.realtest			, sizeof(stB6011.realtest			), INSERT_REAL		);
		insert(pstRoot, "boardid"		, stB6011.boardid			, sizeof(stB6011.boardid			), INSERT_STRING	);
		insert(pstRoot, "yeprice"		, stB6011.yeprice			, sizeof(stB6011.yeprice			), INSERT_INTEGER   );
		insert(pstRoot, "yevolume"		, stB6011.yevolume			, sizeof(stB6011.yevolume			), INSERT_INTEGER   );
		insert(pstRoot, "bddirgb"		, stB6011.bddirgb			, sizeof(stB6011.bddirgb			), INSERT_STRING	);
		insert(pstRoot, "filler"		, stB6011.filler			, sizeof(stB6011.filler				), INSERT_NULL		);

#if 1
		pstRootRoot = json_object();
		json_object_set(pstRootRoot, "hogaData", pstRoot);
#endif
		
		// json메시지로부터 호가 구조체를 생성
		memset(&stOrder, 0x00, sizeof(stOrder));
		memcpy(stOrder.dgubun	, json_string_value(json_object_get(pstRoot, "dgubun"	)), sizeof(stOrder.dgubun	) - 1);
		memcpy(stOrder.expcode	, json_string_value(json_object_get(pstRoot, "expcode")), sizeof(stOrder.expcode	) - 1);

		stOrder.seqno			= json_integer_value(json_object_get(pstRoot, "seqno"			));
		stOrder.volume			= json_integer_value(json_object_get(pstRoot, "volume"		));

		pstArray = json_object_get(pstRoot, "hoga");

		if(json_array_size(pstArray) != 10) {
			printf("Error : pstArray size[%d] != 10\n", json_array_size(pstArray));
			return 0;
		}

		for(i = 0; i < 10; i++) {
			pstValue = json_array_get(pstArray, i);
			stOrder.hoga[i].offer		= json_integer_value(json_object_get(pstValue, "offer"		));
			stOrder.hoga[i].bid			= json_integer_value(json_object_get(pstValue, "bid"		));
			stOrder.hoga[i].offerrem	= json_integer_value(json_object_get(pstValue, "offerrem"	));
			stOrder.hoga[i].bidrem		= json_integer_value(json_object_get(pstValue, "bidrem"		));
		}

		stOrder.T_offerrem		= json_integer_value(json_object_get(pstRoot, "T_offerrem"	));
		stOrder.T_bidrem		= json_integer_value(json_object_get(pstRoot, "T_bidrem"	));
		stOrder.ptmofferrem		= json_integer_value(json_object_get(pstRoot, "ptmofferrem"	));
		stOrder.ptmbidrem		= json_integer_value(json_object_get(pstRoot, "ptmbidrem"	));
		stOrder.otmofferrem		= json_integer_value(json_object_get(pstRoot, "otmofferrem"	));
		stOrder.otmbidrem		= json_integer_value(json_object_get(pstRoot, "otmbidrem"	));

		memcpy(stOrder.sid		, json_string_value(json_object_get(pstRoot, "sid"		)), sizeof(stOrder.sid		) - 1);
		memcpy(stOrder.boardid	, json_string_value(json_object_get(pstRoot, "boardid"	)), sizeof(stOrder.boardid	) - 1);

		if(json_object_get(pstRoot, "booltest1") == json_true())	stOrder.booltest1 = TRUE;
		else														stOrder.booltest1 = FALSE;
		if(json_object_get(pstRoot, "booltest2") == json_true())	stOrder.booltest2 = TRUE;
		else														stOrder.booltest2 = FALSE;
		stOrder.realtest		= json_real_value(json_object_get(pstRoot, "realtest"	));

		stOrder.yeprice			= json_integer_value(json_object_get(pstRoot, "yeprice"	));
		stOrder.yevolume		= json_integer_value(json_object_get(pstRoot, "yevolume"));

		memcpy(stOrder.bddirgb	, json_string_value(json_object_get(pstRoot, "bddirgb"	)), sizeof(stOrder.bddirgb	) - 1);

		if((lLoop + 1) != lTestCnt) {
			json_decref(pstRoot);
		}
	}

	lEnd = kplpGetMonotonicTime(NULL, KPLP_TIME_NS);

	// JSON_PRESERVE_ORDER - 입력순서대로 json메시지를 출력
#if 1
	szString = json_dumps(pstRootRoot, JSON_PRESERVE_ORDER);
#else
	szString = json_dumps(pstRoot, JSON_PRESERVE_ORDER);
#endif
	printf("==============================================================================================\n");
	printf("2. 생성된 JSON메시지 출력 :\n");
	printf("json_dumps => %s\n\n\n", szString);
	free(szString);
#if 1
	json_decref(pstRootRoot);
#else
	json_decref(pstRoot);
#endif

	printf("==============================================================================================\n");
	printf("3. JSON메시지로부터 추출된 값으로 설정한 구조체 출력 :\n");
	printf("dgubun[%s] expcode[%s] seqno[%d] volume[%ld] \
offer1[%ld] bid1[%ld] offerrem1[%ld] bidrem1[%ld] \
offer2[%ld] bid2[%ld] offerrem2[%ld] bidrem2[%ld] \
offer3[%ld] bid3[%ld] offerrem3[%ld] bidrem3[%ld] \
offer4[%ld] bid4[%ld] offerrem4[%ld] bidrem4[%ld] \
offer5[%ld] bid5[%ld] offerrem5[%ld] bidrem5[%ld] \
offer6[%ld] bid6[%ld] offerrem6[%ld] bidrem6[%ld] \
offer7[%ld] bid7[%ld] offerrem7[%ld] bidrem7[%ld] \
offer8[%ld] bid8[%ld] offerrem8[%ld] bidrem8[%ld] \
offer9[%ld] bid9[%ld] offerrem9[%ld] bidrem9[%ld] \
offer10[%ld] bid10[%ld] offerrem10[%ld] bidrem10[%ld] \
T_offerrem[%ld] T_bidrem[%ld] ptmofferrem[%ld] ptmbidrem[%ld] \
otmofferrem[%ld] otmbidrem[%ld] sid[%s] boardid[%s] \
booltest1[%d] booltest2[%d] realtest[%f] \
yeprice[%ld] yevolume[%ld] bddirgb[%s] filler[%s]\n\n\n",
			stOrder.dgubun, stOrder.expcode, stOrder.seqno, stOrder.volume,
			stOrder.hoga[0].offer, stOrder.hoga[0].bid, stOrder.hoga[0].offerrem, stOrder.hoga[0].bidrem,
			stOrder.hoga[1].offer, stOrder.hoga[1].bid, stOrder.hoga[1].offerrem, stOrder.hoga[1].bidrem,
			stOrder.hoga[2].offer, stOrder.hoga[2].bid, stOrder.hoga[2].offerrem, stOrder.hoga[2].bidrem,
			stOrder.hoga[3].offer, stOrder.hoga[3].bid, stOrder.hoga[3].offerrem, stOrder.hoga[3].bidrem,
			stOrder.hoga[4].offer, stOrder.hoga[4].bid, stOrder.hoga[4].offerrem, stOrder.hoga[4].bidrem,
			stOrder.hoga[5].offer, stOrder.hoga[5].bid, stOrder.hoga[5].offerrem, stOrder.hoga[5].bidrem,
			stOrder.hoga[6].offer, stOrder.hoga[6].bid, stOrder.hoga[6].offerrem, stOrder.hoga[6].bidrem,
			stOrder.hoga[7].offer, stOrder.hoga[7].bid, stOrder.hoga[7].offerrem, stOrder.hoga[7].bidrem,
			stOrder.hoga[8].offer, stOrder.hoga[8].bid, stOrder.hoga[8].offerrem, stOrder.hoga[8].bidrem,
			stOrder.hoga[9].offer, stOrder.hoga[9].bid, stOrder.hoga[9].offerrem, stOrder.hoga[9].bidrem,
			stOrder.T_offerrem, stOrder.T_bidrem, stOrder.ptmofferrem, stOrder.ptmbidrem,
			stOrder.otmofferrem, stOrder.otmbidrem, stOrder.sid, stOrder.boardid,
			stOrder.booltest1, stOrder.booltest2, stOrder.realtest,
			stOrder.yeprice, stOrder.yevolume, stOrder.bddirgb, stOrder.filler);

	printf("==============================================================================================\n");
	printf("결과 : 테스트건수[%ld] 총걸린시간[%ld 나노초] 건당걸린시간[%ld 나노초]\n", lTestCnt, lEnd - lStart, (lEnd - lStart) / lTestCnt);
	printf("==============================================================================================\n");

	return 1;
}
