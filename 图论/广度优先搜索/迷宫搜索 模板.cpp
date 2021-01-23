#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

//************ �Թ��� ����������� ģ�� ************
const int MAXQUEUE = 1000000;                         // ����ѭ�����У����Կ��Բ��úܴ�
const int MAXN = 110;                                 // ��ͼ�Ĵ�С
const int DIR_COUNT = 4;                              // ������
const int inf = -1;

enum eDirection {
    ED_RIGHT = 0,
    ED_UP = 1,
    ED_LEFT = 2,
    ED_DOWN = 3,
};

const int dir[DIR_COUNT][2] = {
    { 0, 1 },   // 0. ��
    { -1, 0 },  // 1. ��
    { 0, -1 },  // 2. ��
    { 1, 0 },   // 3. ��
};

int getDirIndex(int dx, int dy) {
    for (int i = 0; i < DIR_COUNT; ++i) {
        if (dx == dir[i][0] && dy == dir[i][1]) {
            return i;
        }
    }
    return -1;
}

int optDir[] = {
    2, 3, 0, 1
};

// ���ѵĵ�ͼ����Ϊȫ�ֱ����洢
char Map[MAXN][MAXN];

// ����ʱ������е�״̬���
struct BFSState {
    int x, y;                              // 1. һ���Թ����ⶼ���е�λ���ֶ�

protected:
    int getStateKey() const;                // 1. ���йؼ��ִ����һ����ϣֵ���й�ϣӳ��

public:

    inline bool isValidState(int row, int col);    // 1. �����Ƿ�Ϸ���һ�����ж� �谭 �ͱ߽�
    inline bool isFinalState();                    // 2. �Ƿ����״̬
    inline int getStep() const;                    // 3. ��ȡ�� ��ʼ״̬ �� ��ǰ״̬�Ĳ���
    inline void setStep(int step);                 // 4. ���ô� ��ʼ״̬ �� ��ǰ״̬�Ĳ���
    inline void print() const;                     // 5. ���Դ�ӡ��ǰ״̬��
    inline bool operator==(const BFSState & o);    // 6. �����ж�����״̬�Ƿ����

public:
    static int step[MAXN][MAXN];                  //  ���״̬��Ӧ�Ĳ���
};


class BFSQueue {
public:
    BFSQueue();
    virtual ~BFSQueue();

    void clear();
    bool empty();
    void push(const BFSState& bs);
    BFSState& pop();
private:
    BFSState *data_;
    int front_, rear_;
};

BFSQueue::BFSQueue() : data_(NULL) {
    data_ = new BFSState[MAXQUEUE];
}

BFSQueue::~BFSQueue() {
    if (data_) {
        delete[] data_;
        data_ = NULL;
    }
}

void BFSQueue::clear() {
    front_ = rear_ = 0;
}

void BFSQueue::push(const BFSState& bs) {
    data_[rear_++] = bs;
    if (rear_ == MAXQUEUE) rear_ = 0;
}

BFSState& BFSQueue::pop(){
    if (++front_ == MAXQUEUE) front_ = 0;
    if (front_ == 0)
        return data_[MAXQUEUE - 1];
    else
        return data_[front_ - 1];
}

bool BFSQueue::empty() {
    return front_ == rear_;
}

class BFSGraph {
public:

    void bfs_extendstate(const BFSState& fromState);
    void bfs_initialize(BFSState startState);
    int  bfs(BFSState startState);
private:
    BFSQueue queue_;
    int uselen_;
};


int BFSState::getStateKey() const {
    // y        : 11111
    // x        : 11111
    return x << 5 | y;
}

bool BFSState::isValidState(int row, int col) {
    if (x < 0 || y < 0 || x >= row || y >= col) {
        return false;
    }
    if (Map[x][y]) {
        return false;
    }
    return true;
}

bool BFSState::isFinalState() {
    return true;
}

int BFSState::getStep() const {
    return step[x][y];
}

void BFSState::setStep(int sp) {
    step[x][y] = sp;
}

void BFSState::print() const {
    printf("%d %d\n", x, y);
}

int BFSState::step[MAXN][MAXN];
int n, m;

void BFSGraph::bfs_extendstate(const BFSState& fromState) {
    int stp = fromState.getStep() + 1;
    BFSState to;

    for (int i = 0; i < DIR_COUNT; ++i) {
        to.x = fromState.x + dir[i][0];
        to.y = fromState.y + dir[i][1];

        if (!to.isValidState(n, m)) {
            continue;
        }

        if (to.getStep() == inf) {
            to.setStep(stp);
            queue_.push(to);
        }
    }
}

void BFSGraph::bfs_initialize(BFSState startState) {
    memset(BFSState::step, -1, sizeof(BFSState::step));
    queue_.clear();
    queue_.push(startState);
    startState.setStep(0);
}

int BFSGraph::bfs(BFSState startState) {
    bfs_initialize(startState);
    while (!queue_.empty()) {
        BFSState bs = queue_.pop();
        if (bs.isFinalState()) {
            return bs.getStep();
        }
        bfs_extendstate(bs);
    }
    return inf;
}

//************ �Թ��� ����������� ģ�� ************

BFSGraph bfs;
