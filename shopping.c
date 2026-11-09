
#include <stdio.h>
#pragma warning(disable:4996)
#include <string.h>
#include <ctype.h>
#define member 5

void swap(int* x, int* y);
void swap_char(char* x, char* y);
void swap_str(char* x, char* y);

int main()
{
    int id[member] = { 101,102,103,105,201 };
    char name[member][20] = { "KIM","LEE","PARK","CHOI","SONG" };
    char rate[member] = { 'R','G','S','G','S' };

    int input_id, i, count, k;
    char input_code;
    int input_stock;
    int pay_method;

    char p_code[member] = { 'A','B','C','D','E' };
    char p_name[member][20] =
    { "Apple","Bread","Coffee","Desk","Euiod" };
    int p_price[member] = { 12000,8000,15000,100000,56000 };
    int p_stock[member] = { 50,30,80,20,70 };

    int tot_buy[member] = { 0 };
    int discount[member] = { 0 };
    int res_pay[member] = { 0 };

    int purchased[member] = { 0 };
    int buyer_count = 0;
    int user_idx, product_idx;
    int tot_sales = 0;

    // 구매자 입력
    while (buyer_count < member)
    {
        printf("\ninput your ID(finish = 0) >>>");
        scanf("%d", &input_id);

        if (input_id == 0)
            break;

        // 회원 검색
        user_idx = -1;

        for (i = 0; i < member; i++)
        {
            if (id[i] == input_id)
            {
                user_idx = i;
                break;
            }
        }

        if (user_idx == -1)
        {
            printf("Non-members cannot make purchases.\n");
            continue;
        }

        if (purchased[user_idx] == 1)
        {
            printf("Already purchased.\n");
            continue;
        }

        printf("how many products? >>>");
        scanf("%d", &count);

        if (count < 1)
        {
            printf("Invalid product count.\n");
            continue;
        }

        // 상품 구매
        for (i = 0; i < count; i++)
        {
            printf("input product's code and quantity >>>");
            scanf(" %c %d", &input_code, &input_stock);

            input_code = toupper((unsigned char)input_code);

            // 상품 검색
            product_idx = -1;

            for (k = 0; k < member; k++)
            {
                if (input_code == p_code[k])
                {
                    product_idx = k;
                    break;
                }
            }

            if (product_idx == -1)
            {
                printf("Invalid product code.\n");
                i--;
                continue;
            }

            // 재고 확인
            if (input_stock <= 0 ||
                input_stock > p_stock[product_idx])
            {
                printf("Insufficient stock. Available: %d\n",
                    p_stock[product_idx]);

                i--;
                continue;
            }

            // 해당 회원의 구매금액 누적
            tot_buy[user_idx] +=
                p_price[product_idx] * input_stock;
        }

        // 결제방법
        printf("input your pay method (credit=1/check=2/cash=3) >>>");
        scanf("%d", &pay_method);

        while (pay_method < 1 || pay_method > 3)
        {
            printf("Invalid pay method. Retry >>>");
            scanf("%d", &pay_method);
        }

        // 회원등급 및 결제방법 할인율
        int r_rate = 0;
        int p_rate = 0;

        if (rate[user_idx] == 'R')
            r_rate = 10;
        else if (rate[user_idx] == 'G')
            r_rate = 7;
        else if (rate[user_idx] == 'S')
            r_rate = 5;

        if (pay_method == 1)
            p_rate = 5;
        else if (pay_method == 2)
            p_rate = 7;
        else if (pay_method == 3)
            p_rate = 10;

        discount[user_idx] =
            tot_buy[user_idx] * (r_rate + p_rate) / 100;

        res_pay[user_idx] =
            tot_buy[user_idx] - discount[user_idx];

        purchased[user_idx] = 1;
        buyer_count++;
    }

    // 선택정렬/내림차순
    for (i = 0; i < member - 1; i++)
    {
        int max_idx = i;

        for (k = i + 1; k < member; k++)
        {
            if (res_pay[k] > res_pay[max_idx])
            {
                max_idx = k;
            }
        }

        if (max_idx != i)
        {
            swap(&id[i], &id[max_idx]);
            swap_str(name[i], name[max_idx]);
            swap_char(&rate[i], &rate[max_idx]);
            swap(&tot_buy[i], &tot_buy[max_idx]);
            swap(&discount[i], &discount[max_idx]);
            swap(&res_pay[i], &res_pay[max_idx]);
            swap(&purchased[i], &purchased[max_idx]);
        }
    }

    // 구매자별 내역 출력
    printf("\n\n- Print list of all buyers -\n");
    printf("----------------------------------------------------------\n");
    printf("%-10s %12s %12s %12s\n",
        "Name", "Total", "Discount", "Payment");

    for (i = 0; i < member; i++)
    {
        if (purchased[i] == 1)
        {
            printf("%-10s %12d %12d %12d\n",
                name[i],
                tot_buy[i],
                discount[i],
                res_pay[i]);

            tot_sales += res_pay[i];
        }
    }

    printf("----------------------------------------------------------\n");

    // 총매출 및 평균 구매금액
    printf("\n- Total daily sales revenue and average purchase amount\n");
    printf("  Total sales : %d\n", tot_sales);

    if (buyer_count > 0)
    {
        printf("  Average Purchase Amount : %.0f\n",
            (double)tot_sales / buyer_count);

        // 최대 구매자
        printf("\n- Maximum purchase amount and maximum buyer\n");
        printf("  Maximum purchase : %d\n", res_pay[0]);
        printf("  Maximum buyer : %s\n", name[0]);
    }
    else
    {
        printf("  No purchases.\n");
    }

    return 0;
}

void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void swap_char(char* x, char* y)
{
    char temp = *x;
    *x = *y;
    *y = temp;
}

void swap_str(char* x, char* y)
{
    char temp[20];
    strcpy(temp, x);
    strcpy(x, y);
    strcpy(y, temp);
}
