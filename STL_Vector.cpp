#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class Stack
{
public:
	Stack() { Clear(); }

	// ���� ����� �����Ѵ�.
	void SetInOutType(bool bLIFO) { m_bLIFO = bLIFO; }

	// �ʱ�ȭ �Ѵ�.
	void Clear()
	{
		if (false == m_Datas.empty())
			m_Datas.clear();
	}

	// ���ÿ� ����� ����
	int Count() { return static_cast(m_Datas.size()); }

	// ����� �����Ͱ� ���°�?
	bool IsEmpty() { return m_Datas.empty(); }


	// �����͸� �����Ѵ�.
	void push(T data)
	{
		m_Datas.push_back(data);
	}

	// ���ÿ��� ������.
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
	bool  m_bLIFO; // true �̸� ���Լ���, false �̸� ���Լ���
};

// ���� ����
struct UserInfo
{
	char acUserName[21]; // �̸�	
	int	Level;       // ����  
	int Exp;             // ����ġ   
};

// ���� ���� ������ �����ϴ� Ŭ����
// �濡�� �ִ� 6����� ��� �� �� �ִ�.
// �濡 ��� ���� ���� �� ���� ���� ��� �� ����� ������ �ȴ�.
class GameRoomUser
{
public:
	//GameRoomUser(); //�� ������ ������ ����?
	//~GameRoomUser();

	// �濡 ���� �߰�
	bool AddUser(UserInfo& tUserInfo)
	{
		if (Users.empty())
			strcpy_s(acMasterUserName, sizeof(acMasterUserName), tUserInfo.acUserName);
		else if (Users.size() > 6)
			return false;

		Users.push_back(tUserInfo);
		return true;

		/*���� §��
		// �����Ʈ : ���ǵ� ������ �� �м��ϴ� �ɷ��� �⸣��.
		if (Users.size() < 7)
		{
		Users.push_back(tUserInfo);
		return true;
		}
		else
		{
		cout << "���� �ʰ��Դϴ�.";
		return false;
		}
		*/
	}

	// �濡�� ���� ����. 
	// ���� ������ ������ acMasterUserName�� ���ο� ������ �̸��� ���� �ؾ� �ȴ�.
	bool DelUser(char* pcUserName)
	{
		if (Users.empty())
			return false;

		if (pcUserName == acMasterUserName) //�����Ϳ� �迭�� �̷��� �񱳰� �ǳ�? �Ϳ�
			*acMasterUserName = *GetUserOfLastOrder().acUserName; //�̰� �� ���� �������� ��

		for (vector< UserInfo >::iterator IterPos = Users.begin();
			IterPos != Users.end();	++IterPos)
		{
			if (strcmp(IterPos->acUserName, pcUserName) == 0)
			{
				Users.erase(IterPos);
				return true;
			}
		}
		/*���� §��
		// �����Ʈ : �̻���� empty �Լ��� �� ����ϳ�
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

	// �濡 ������ ���� ������. ������ true ��ȯ
	bool IsEmpty()
	{
		return Users.empty();
	}

	// �濡 ������ �� á���� ����. �� á�ٸ� true ��ȯ
	bool IsFull()
	{
		return !(Users.empty());
		/* ���� ���� �ѹ濡 �ǳ�
		if (Users.size() == 6)
			return true;
		else
			return false;
		*/
	}

	// Ư�� ������ ����
	UserInfo& GetUserOfName(char* pcName)
	{
		//�̰� ���� �� ������ ������?
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

	// ������ ���� ����
	UserInfo& GetMasterUser()
	{
		//�̰͵� ���� �� �������� ������
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

	// ���� �������� �濡 ��� �� ������ ����
	UserInfo& GetUserOfLastOrder()
	{
		return Users.back();

		//�����Ʈ : ������ �Լ��� ����� �����߳�
		//return Users[Users.size()];
	}

	// Ư�� ������ ��� �� ������ �i�Ƴ���.
	bool BanUser(int OrderNum)
	{
		vector< UserInfo >::iterator iterPos = Users.begin();
		Users.erase(iterPos + OrderNum);
	}

	// ��� ������ �����Ѵ�.
	void Clear()
	{
		Users.clear();
	}

private:
	vector< UserInfo > Users;
	char acMasterUserName[21]; // ������ �̸�

};

void main()
{
	/*
	Stack< int > Int_Stack;

	// LIFO�� ����
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
	sprintf_s(UserB.acUserName, "���̿�������");
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

	Room1.DelUser("���̿�������");
	Room1.AddUser(UserC);

	cout << Room1.GetUserOfLastOrder().acUserName << endl;

	return;
}