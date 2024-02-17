#include <bits/stdc++.h>

char map[10][10];
int visited[10][10];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};
int rows, cols, moveCount;
std::string str;
std::pair<int, int> start;
std::pair<int, int> end;

    
int RouteCountInMoveCnt(int y, int x)
{
    // DFS 기저조건 : 목적지 도착하면 탈출
    if (y == end.first && x == end.second)
    {
        // 이동수에 맞추어 목적지 도착 확인
        if(moveCount == visited[y][x])
        {
            return 1;
        }
        else
        {
            return 0;   
        }
    }
    
    int ret = 0;
    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];

        // 예외조건, T 는 이동 불가 영역
        if (nx < 0 || ny < 0 || nx >= cols || ny >= rows || visited[ny][nx] || map[ny][nx] == 'T') continue;
        
        visited[ny][nx] = visited[y][x] + 1;
        // 해당 위치를 이동하는 경우의 목적지 도착 결과 추가
        ret += RouteCountInMoveCnt(ny, nx);
        // 해당 위치의 경우의 수를 리셋. 
        visited[ny][nx] = 0;
    }
    return ret;
}

int main() {

    std::cin >> rows >> cols >> moveCount;
    for (int i = 0; i < rows; i++)
    {
        std::cin >> str;
        for (int j = 0; j < cols; j++)
        {
            // . 은 이동 가능, T 는 이동불가
            map[i][j] = str[j];
        }
    }
    
    // 시작점 좌측하단
    // 도착점 우측상단
    start = std::make_pair(rows-1, 0);
    end = std::make_pair(0, cols -1);

    // start point
    visited[start.first][start.second] = 1;
    
    std::cout << RouteCountInMoveCnt(start.first, start.second) << std::endl;
    
}

// -------------------------------------------------------------------------------------------

#include <bits/stdc++.h>

int mapPrices[20][20];
int visited[20][20];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int sqMapSize; 
int retPrice = 999999999;
int limitFlowerCnt = 3;

int calMapPriceForFlower(int y, int x)
{
	// 꽃을 배치한 지역 방문 처리
    visited[y][x] = 1;
	// 꽃이 심어지는 위치와 만개하는 영역에 대한 땅 가격을 계산
    int price = mapPrices[y][x]; // 꽃을 심는 영역 가격 추가
    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        visited[ny][nx] = 1; // 꽃이 피는 지역 방문 처리
        price += mapPrices[ny][nx]; // 꽃이 피는 영역 가격 추가
    }
    return price;
}

int checkFlowerRange(int y, int x)
{
    // DFS 탈출조건
    if (visited[y][x]) return 0;
    // 현재위치(x,y) 에서 꽃의 전개 가능 영역 확인 
    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || ny < 0 || nx >= sqMapSize || ny >= sqMapSize || visited[ny][nx])
        {
            return 0;
        }  
    }
    return 1;
}

void resetFlower(int y, int x)
{
    // 꽃을 심는 위치와 꽃의 전개 영역을 리셋한다
    visited[y][x] = 0;
    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        visited[ny][nx] = 0;
    }
}

void setFlowerNFindMinPrice(int flowerCnt, int totalPrice)
{
    // DFS 탈출 조건 (기저조건)
    // 전체 경우의 수에서 최저 가격을 기록
    if (flowerCnt == limitFlowerCnt)
    {
        retPrice = std::min(retPrice, totalPrice);
        return;
    }
    
    for (int i = 0; i < sqMapSize; i++)
    {
        for (int j = 0; j < sqMapSize; j++)
        {
            // 현재 위치에서 꽃이 만개할 수 있는지 확인 
            if (checkFlowerRange(i, j))
            {
                //해당 위치에 꽃을 하나 위치시키고 다음 꽃은 배치 
                setFlowerNFindMinPrice(flowerCnt + 1, totalPrice + calMapPriceForFlower(i, j));
                // 해당 꽃 배치 경우가 끝나면 다른 경우를 위해 배치한 꽃을 방문 기록에서 리셋 
                resetFlower(i, j);
            }
        }
    }
}

int main() {
    std::cin >> sqMapSize;
    for (int i = 0; i < sqMapSize; i++)
    {
        for (int j = 0; j < sqMapSize; j++)
        {
            // 맵 구역(y,x) 마다의 가격 등록
            std::cin >> mapPrices[i][j];
        }
    }
    
    // N 개의 꽃이 피는 영역을 고려한 최소한의 맵 가격 찾기
    setFlowerNFindMinPrice(0, 0);
    
    std::cout << retPrice << std::endl;
}

// --------------------------------------------------------------------------------

#include <bits/stdc++.h>

int gearCnt;
// 기어이는 기어당 8개이며 
// 기어정보는 1과0으로 S,N 극으로 총 8개의 문자로 이루어진다. 
// 기어이의 순서는 12시 방향으로 시계 방향 순서대로 주어진다.
std::string gearTeethInfo[1001]; // 기어수는 최대 1000개

void rotateGear(int pos, int dir)
{
	// ccw 1칸 이동
	if (!dir) std::rotate(gearTeethInfo[pos].begin(), gearTeethInfo[pos].begin() + 1, gearTeethInfo[pos].end());
	// cw 1칸 이동
	else std::rotate(gearTeethInfo[pos].begin(), gearTeethInfo[pos].begin() + gearTeethInfo[pos].size() - 1, gearTeethInfo[pos].end());
}

// 선택한 기어 왼쪽에 기어들 확인
// 기어이가 8개 라는 전재가 있으며 idx=2 와 idx=6 의 기어이가 맞물린다.  
// 해당 idx=2,6 사이의 극 확인하고 영향 변화
int findLastLeftGearInInEffect(int pos)
{
	// 현재 기어의 왼쪽기어들 탐색 
    for (int i = pos; i >= 1; i--)
    {
		// 서로 극이 같게 되는 기어 위치 출력 (이후의 왼쪽 기어들은 회전영향 없게되므로)
		// 영향을 미치는 기어의 최대 왼쪽 위치 출력 
        if (gearTeethInfo[i][6] == gearTeethInfo[i-1][2])
        {
            return i;
        }
    }
	return 0;
}

int findLastRightGearInInEffect(int pos)
{
	// 오른쪽 기어들 탐색
    for (int i = pos; i <= gearCnt - 2; i++)
	{	
		// 서로 극이 같게 되는 기어 위치 출력 (이후의 오른쪽 기어들은 회전영향 없게됨)
		// 영향을 미치는 기어의 최대 오른쪽 위치 출력 
		if (gearTeethInfo[i][2] == gearTeethInfo[i+1][6])
		{
			return i;
		}
	}
	return gearCnt - 1;
}

int main() {
    std::cin >> gearCnt; // 총 기어 개수
    for (int i = 0; i < gearCnt; i++)
    {
        // gearTeethInfo 는 총 8개의 기어이가 있으며 각 이는 N극 S극 정보가 있다. 
        // 서로 다른 극이 맞물려 회전하면 각자 반대 방향으로 회전하고 극이 같으면 회전하지 않는다. 
		// ex) 10101111 == SNSNSSSS
        std::cin >> gearTeethInfo[i];
    }
    
    int rotCnt; // 기어 회전 횟수
    std::cin >> rotCnt;
	
	int choosedGear; // 회전시킬 기어
	int rotDirection; // 기어 회전 방향 : 1 (CW), 0 (CCW)
    
    for (int i = 0; i < rotCnt; i++)
    {
        std::cin >> choosedGear >> rotDirection;
        choosedGear -= 1; // Index 맞추기 
        // 1 : cw , -1 : ccw ==> true, false 용으로 전환 
        rotDirection = (rotDirection == -1 ? 0 : 1);
        
		// 현재 기어의 회전에 따른 좌, 우측 영향을 받는 기어의 끝 위치 
		// 극이 서로 다르게 물려있는 기어들의 좌우 끝 위치 
        int leftGear = findLastLeftGearInInEffect(choosedGear);
		int rightGear = findLastRightGearInInEffect(choosedGear);
		
		// 현재 기어의 회전에 따라 영향받는 좌측 기어들의 회전
		// cnt 는 홀수, 짝수를 표현 
		int cnt = 0;
		for (int pos = choosedGear; pos >= leftGear; pos--)
		{
			rotateGear(pos, cnt % 2 == 0 ? rotDirection : !rotDirection);
			cnt++;
		}
		
		// 현재 기어의 회전에 따라 영향받는 우측 기어들의 회전
		cnt = 1;
		for (int pos = choosedGear + 1; pos <= rightGear; pos++)
		{
			rotateGear(pos, cnt % 2 == 0 ? rotDirection : !rotDirection);
			cnt++;
		}    
    }
    
	// 12시 방향이 S극 (==1) 인 기어 개수 출력
    int ret = 0;
	for (int i = 0; i < gearCnt; i++)
	{
		if (gearTeethInfo[i][0] == '1')
		{
			ret++;
		}
	}
	
	std::cout << ret << std::endl;
    
}

// -----------------------------------------------------------------------------------------
