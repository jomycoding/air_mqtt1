#ifndef CALC_CONFIG_H    // CALC_CONFIG_H가 정의되어 있지 않다면
#define CALC_CONFIG_H    // CALC_CONFIG_H 매크로 정의


/*
 * 아래의 경우를 제외하고 미세먼지 수치(PM2.5)만 큰 글씨로 화면에 출력되고,
 * 이 때 상단에 온도,습도 작은글씨로 표기됨.
 * 
 * 습도가 낮은 경우 100% 이하에서 수치가 oled에 다음화면에 출력되며, 습도가 36%보다 작은 경우에는 경고문구가 나옴.
 * 온도가 높은 경우 -100도 이상에서 수치가 oled에 다음화면에 출력되며, 온도가 33도보다 큰 경우에는 경고문구가 나옴.
 * DHT 온도보정  : -1.0도
*/


#define REF_HU 42.0 // for mom 42.0% 이하만 출력(case1), (case2)모두출력 100.0,  (case3) 계절따라 50.0% 이하만
#define REF_HU_wet 80.0 // for 여름 80% 이상일 때 출력
#define REF_HU_WARN 36.0 //36%
#define REF_TE 28.0 // for mom 28.0도 이상에서 출력(case1), (case2)모두출력 -100.0, (case3) 계절따라 28.0도 이상만
#define REF_TE_WARN 33.0 //33.0도

#define Delta_HU -3.0 // 습도보정 defalut -3.0
#define Delta_TE -1.5 // 온도보정 defalut -1.5  


/*
 * PM25 설정
 */

#define REF_PM25_WARN 50 //jm
#define NUM_SAMPLE 15 //jm


#endif                               // #ifndef CALC_CONFIG_H 끝
