#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class Stack
{
public:
	Stack() { Clear(); }

	// 저장 방식을 설정한다.
	void SetInOutType(bool bLIFO) { m_bLIFO = bLIFO; }

	// 초기화 한다.
	void Clear()
	{
		if (false == m_Datas.empty())
			m_Datas.clear();
	}

	// 스택에 저장된 개수
	int Count() { return static_cast(m_Datas.size()); }

	// 저장된 데이터가 없는가?
	bool IsEmpty() { return m_Datas.empty(); }


	// 데이터를 저장한다.
	void push(T data)
	{
		m_Datas.push_back(data);
	}

	// 스택에서 빼낸다.
	bool pop(T* data)
	{
		if (IsEmpty())
		{
			return false;
		}

		if (m_bLIFO)
		{
			memcpy(data, &m_Datas.back(), sizeof(T));
			m_Datas.pop_back();
		}
	
		return true;
	}

private:
	vector<T> m_Datas;
	bool  m_bLIFO; // true 이면 후입선출, false 이면 선입선출
};

// 유저 정보
struct UserInfo
{
	char acUserName[21]; // 이름	
	int	Level;       // 레벨  
	int Exp;             // 경험치   
};

// 게임 방의 유저를 관리하는 클래스
// 방에는 최대 6명까지 들어 갈 수 있다.
// 방에 들어 오는 순서 중 가장 먼저 들어 온 사람이 방장이 된다.
class GameRoomUser
{
public:
	//GameRoomUser(); //왜 컴파일 에러가 나지?
	//~GameRoomUser();

	// 방에 유저 추가
	bool AddUser(UserInfo& tUserInfo)
	{
		if (Users.empty())
			strcpy_s(acMasterUserName, sizeof(acMasterUserName), tUserInfo.acUserName);
		else if (Users.size() > 6)
			return false;

		Users.push_back(tUserInfo);
		return true;

		/*내가 짠거
		// 오답오트 : 정의된 문제를 잘 분석하는 능력을 기르자.
		if (Users.size() < 7)
		{
		Users.push_back(tUserInfo);
		return true;
		}
		else
		{
		cout << "정원 초과입니다.";
		return false;
		}
		*/
	}

	// 방에서 유저 삭제. 
	// 만약 방장이 나가면 acMasterUserName에 새로운 방장의 이름을 설정 해야 된다.
	bool DelUser(char* pcUserName)
	{
		if (Users.empty())
			return false;

		if (pcUserName == acMasterUserName) //포인터와 배열이 이렇게 비교가 되나? 와우
			*acMasterUserName = *GetUserOfLastOrder().acUserName; //이건 또 무슨 문법이지 ㅜ

		for (vector< UserInfo >::iterator IterPos = Users.begin();
			IterPos != Users.end();	++IterPos)
		{
			if (strcmp(IterPos->acUserName, pcUserName) == 0)
			{
				Users.erase(IterPos);
				return true;
			}
		}
		/*내가 짠거
		// 오답오트 : 이사람은 empty 함수를 잘 사용하네
		for (vector< UserInfo >::iterator IterPos = Users.begin();
			IterPos != Users.end();	++IterPos)
		{
			if (strcmp(IterPos->acUserName, pcUserName) == 0)
			{
				Users.erase(IterPos);
			}
		}
		*/
	}

	// 방에 유저가 없는 지조사. 없으면 true 반환
	bool IsEmpty()
	{
		return Users.empty();
	}

	// 방에 유저가 꽉 찼는지 조사. 꽉 찼다면 true 반환
	bool IsFull()
	{
		return !(Users.empty());
		/* 위에 꺼는 한방에 되네
		if (Users.size() == 6)
			return true;
		else
			return false;
		*/
	}

	// 특정 유저의 정보
	UserInfo& GetUserOfName(char* pcName)
	{
		//이건 내가 더 좋은거 같은데?
		for (int i = 0; i < Users.size(); i++)
		{
			if (strcmp(Users[i].acUserName, pcName) == 0)
				return Users[i];
		}
		/*
		vector<UserInfo>::iterator iterPos = Users.begin();
		int i = 0;

		while (iterPos->acUserName != pcName)
		{
			iterPos++;
			i++;
		}
		return Users.at(i);
		*/
		
	}

	// 방장의 유저 정보
	UserInfo& GetMasterUser()
	{
		//이것도 내가 더 괜찮은거 같은디
		for (int i = 0; i < Users.size(); i++)
		{
			if (strcmp(Users[i].acUserName, acMasterUserName) == 0)
				return Users[i];
		}
		/*
		vector<UserInfo>::iterator iterPos = Users.begin();
		int i = 0;

		while (iterPos->acUserName != acMasterUserName)
		{
			iterPos++;
			i++;
		}
		return Users.at(i);
		*/
	}

	// 가장 마지막에 방에 들어 온 유저의 정보
	UserInfo& GetUserOfLastOrder()
	{
		return Users.back();

		//오답노트 : 위에는 함수를 제대로 이해했네
		//return Users[Users.size()];
	}

	// 특정 순서에 들어 온 유저를 쫒아낸다.
	bool BanUser(int OrderNum)
	{
		vector< UserInfo >::iterator iterPos = Users.begin();
		Users.erase(iterPos + OrderNum);
	}

	// 모든 유저를 삭제한다.
	void Clear()
	{
		Users.clear();
	}

private:
	vector< UserInfo > Users;
	char acMasterUserName[21]; // 방장의 이름

};

void main()
{
	/*
	Stack< int > Int_Stack;

	// LIFO로 설정
	Int_Stack.SetInOutType(true);

	Int_Stack.push(10);
	Int_Stack.push(20);
	Int_Stack.push(30);

	int Value = 0;
	Int_Stack.pop(&Value);
	cout << "LIFO pop : " << Value << endl << endl;

	Int_Stack.Clear();
	*/
	GameRoomUser Room1;
	struct UserInfo UserA;
	struct UserInfo UserB;
	struct UserInfo UserC;

	sprintf_s(UserA.acUserName, "Mush");
	sprintf_s(UserB.acUserName, "하이엘프도적");
	sprintf_s(UserC.acUserName, "test123");

	UserA.Exp = 123123;
	UserB.Exp = 11;
	UserC.Exp = 16578;

	UserA.Level = 80;
	UserB.Level = 80;
	UserC.Level = 80;

	Room1.AddUser(UserA);
	Room1.AddUser(UserB);

	cout << Room1.GetUserOfLastOrder().acUserName << endl;

	Room1.DelUser("하이엘프도적");
	Room1.AddUser(UserC);

	cout << Room1.GetUserOfLastOrder().acUserName << endl;

	return;
}