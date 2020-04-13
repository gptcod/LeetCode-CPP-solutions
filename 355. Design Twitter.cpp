#include "leetcode.h"

class Twitter {
public:
    using Tweet = pair<int, size_t>;

    explicit Twitter() { timestamp = 0; };

    void postTweet(int userId, int tweetId) {
        this->tweets[userId].insert(make_pair(tweetId, ++this->timestamp));
    }

    vector<int> getNewsFeed(int userId) {
        priority_queue<Tweet, vector<Tweet>, function<bool(Tweet, Tweet)>> pq([](const Tweet &lhs, const Tweet &rhs) {
            return lhs.second < rhs.second; // 通过时间戳比较推文推送优先级
        });

        for (const auto &followee: this->following[userId]) {
            for (const auto &tweet: this->tweets[followee]) {
                pq.push(tweet); // 查看关注推文
            }
        }

        for (const auto &tweet: this->tweets[userId]) {
            pq.push(tweet); // 查看自身推文
        }

        vector<int> feed;

        int feedCount = min(10, static_cast<int>(pq.size())); // 如有需要 可以使用多路归并的思路来减少运算量
        for (int i = 1; i <= feedCount; ++i) {
            feed.push_back(pq.top().first);
            pq.pop();
        }

        return feed;
    }

    void follow(int followerId, int followeeId) {
        if (followerId == followeeId) { return; } // 不处理关注自身的情况 以避免重复推送

        this->following[followerId].insert(followeeId);
    }

    void unfollow(int followerId, int followeeId) { // 不处理关注自身的情况 以避免重复推送
        if (followerId == followeeId) { return; }

        auto it = this->following[followerId].find(followeeId);

        if (it != this->following[followerId].end()) {
            this->following[followerId].erase(it);
        }
    }

private:
    unordered_map<int, unordered_set<int>> following; // 关注 (followerId -> followeeId)
    unordered_map<int, set<Tweet>> tweets; // 推文列表 (userId -> (tweetId, tweetTimestamp))

    size_t timestamp; // 时间戳 每次产生新推文时自增
};
