// 괄호 균형이 맞는지 확인하라 

bool isBalanceBracket(std::string str)
{
	// 0. 짝이 맞는지 확인을 위한 stack 자료형 준비 
	std::stack<int> stk;
	
	bool check = true;

	//1. 문자열의 문자들을 하나씩 확인한다.
	for (int i = 0; i < str.length(); i++)
	{
		// 2. 시작 괄호이면 스택에 추가한다. 
		// 2-1. 소,중,대괄호
		if (str[i] == '(') stk.push(str[i]);
		if (str[i] == '[') stk.push(str[i]);
		
		// 3. 끝 괄호이면 스택에서 뺀다.
		if (str[i] == ')')
		{
			// 4. 스택에 넣은 시작 괄호와 짝이 않맞으면 탈락
			if (stk.size() == 0 || stk.top() == '[')
			{
				check = false;
				break;
			}
			else
			{
				stk.pop();
			}
		}
		
		// 3. 끝 괄호이면 스택에서 뺀다.
		if (str[i] == ']')
		{
			// 4. 스택에 넣은 시작 괄호와 짝이 않맞으면 탈락
			if (stk.size() == 0 || stk.top() == '(')
			{
				check = false;
				break;
			}
			else
			{
				stk.pop();
			}	
		}
	}
	
	// 괄호가 대칭 조건인지 확인
	if (check && stk.size() == 0) return true;
	else return false;
}

// 올바른 괄호쌍을 이루는 부분의 최대 길이를 구하라

int calcBracketMaxLength(std::string str)
{
    // 0. 최대 길이 리턴
    int ret = 0;

    // 1. 괄호를 쌍을 맞추는데 확인하기 위한 스택 생성
    std::stack<int> stk;
    stk.push(-1); // 괄호쌍이 없는 경우를 위해
   
    for (int i = 0; i < str.length(); i++)
    {
        // 2. 시작 괄호이면 스택에 문자 위치 저장
        if (str[i] == '(') stk.push(i);
        // 3. 끝 괄호이면 스택에서 문자 위치를 뺀다
        if (str[i] == ')')
        {
            stk.pop();
            // 3-1. 스택이 끝나지 않았다면 현재까지의 쌍의 최대 길이를 업데이트 한다.
            if (!stk.empty())
            {
                 // 괄호의 쌍이 성립되는 시작부터 성립의 끝까지의 길이 계산
        	 ret = max(ret, i - stk.top());
            }
            else
            {
                stk.push(i);
            }
        }
    }
    return ret;
}

// 교차하지 않도록 최소 제거 라인 개수 구하기 (DP, 최대 증가수열)

int calcCrossLines(vector<pair<int, int>> lines)
{
    // 0. 선 개수 , dp 배열 , 결과값 저장
    int lineSize = lines.size();
    int dp[100];
    int res = 0;

    // 1. 교차하지 않는 것은 왼쪽을 기준으로 정렬했을 때 오른쪽 값이 전보다 커야 한다.

    // 2. 선들을 정렬한다.
    sort(lines.begin(), lines.end());
   
    // 3. 왼쪽 정렬 상태에서 오른쪽 값들의 최대 증가 수열 수를 구해 전체 라인 수에서 뺸다.
    for (int i = 0; i < lineSize; i++)
    {
        // 3-1. 최대 증가 수열을 구해 dp 에 저장한다. 가장 긴수를  res 에 저장한다.       
        dp[i] = 1;
        for (int j = 0; j < i; j++)
        {
            if (lines[j].second < lines[i].second)
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
           
            res = max(res, dp[i]);
        }
    }
   
    return lineSize - res;
}

