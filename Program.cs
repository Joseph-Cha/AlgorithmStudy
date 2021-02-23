﻿/*
문제)
10952번
두 정수 A와 B를 입력받은 다음, A+B를 출력하는 프로그램을 작성하시오.
*/

/*
입력)
입력은 여러 개의 테스트 케이스로 이루어져 있다.
각 테스트 케이스는 한 줄로 이루어져 있으며, 각 줄에 A와 B가 주어진다. (0 < A, B < 10)
입력의 마지막에는 0 두 개가 들어온다.
*/

using System.Text;

class Program
{
    static void Main()
    {
        StringBuilder sb = new StringBuilder();
        int A;
        int B;
        int sum;
        while(true)
        {
            string[] input = System.Console.ReadLine().Split(" ");
            if(input.Length == 1)
            {
                break;
            }
            int.TryParse(input[0], out A);
            int.TryParse(input[1], out B);
            sum = A + B;
            System.Console.WriteLine(sum.ToString());
        }

    }
}
