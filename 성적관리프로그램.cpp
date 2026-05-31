#include <stdio.h>
#pragma warning(disable:4996)

int main()
{
	int num[100], cla[20], kor[100], eng[100], math[100], tot_score[100], rank[100];//평균 소수 둘째까지
	char initial[100];
	double avg[100], kor_avg, eng_avg, math_avg;
	int i, j, stu_num, kor_tot = 0, eng_tot = 0, math_tot = 0, hkor, heng, hmath, hkor_num, heng_num, hmath_num;

	printf("How many students are in this class?");
	scanf("%d", &stu_num);	

	for (i = 0;i < stu_num;i++)
	{
		printf("Input student's number, initial, kor_score, eng_score, math_score.\n>>>");
		scanf("%d %c %d %d %d", &num[i], &initial[i], &kor[i], &eng[i], &math[i]);

		if (num[i] < 0 || kor[i] < 0 || eng[i] < 0 || math[i] < 0 || kor[i]>100 || eng[i]>100 || math[i]>100||num[i]==num[i-1])
		{
			printf("It is wrong. Try again"); //잘못된 수 입력시 return
			return 0;
		}
		
		if (initial[i] >= 'a' && initial[i] <= 'z') //대문자 출력
		{
			initial[i] -= 32;
		}

		tot_score[i] = kor[i] + eng[i] + math[i];
		kor_tot += kor[i];
		eng_tot += eng[i];
		math_tot += math[i];
		avg[i] = (double)tot_score[i] / 3;
	}

	for (i = 0;i < stu_num;i++)
	{
		rank[i] = 1;
		for (j = 0;j < stu_num;j++)
		{
			if (avg[i] < avg[j])
			{
				rank[i] += 1;
			}
		}
	}

	hkor = kor[0]; heng = eng[0]; hmath = math[0];
	hkor_num = num[0]; heng_num = num[0]; hmath_num = num[0];
	for (i = 1;i < stu_num;i++)
	{
		if (kor[i] > hkor)
		{
			hkor = kor[i];
			hkor_num = num[i];
		}
		if (eng[i] > heng)
		{
			heng = eng[i];
			heng_num = num[i];
		}
		if (math[i] > hmath)
		{
			hmath = math[i];
			hmath_num = num[i];
		}
	}

	for (i = 0;i < stu_num;i++)
	{
		printf("\n\n %d\t%c\t%d\t%d\t%d\t%d\t%.2lf\t%d\n", num[i], initial[i], kor[i], eng[i], math[i], tot_score[i], avg[i], rank[i]);
	}

	kor_avg = (double)kor_tot / stu_num;
	eng_avg = (double)eng_tot / stu_num;
	math_avg = (double)math_tot / stu_num;
	printf("\n\n The average of each subhject is\n>> kor:%.2lf \teng:%.2lf \tmath:%.2lf", kor_avg, eng_avg, math_avg);
	printf("\n\n highest score student is \n kor:num %d\tscore %d\n eng:num %d\tscore %d\n math:num %d\tscore %d\n\n\n", hkor_num, hkor, heng_num, heng, hmath_num, hmath);

	printf("Enter the initials of the students you want to check.");
	scanf(" %c", &initial[i]);
	for (i = 0;i < stu_num;i++)
	{
		printf("\n\n %d\t%c\t%d\t%d\t%d\t%d\t%.2lf\t%d\n", num[i], initial[i], kor[i], eng[i], math[i], tot_score[i], avg[i], rank[i]);
		break;
	}
	return 0;
}