#include "leetcode.h"

class Solution {
public:
    static constexpr double EPS = 1e-6;

    vector<double> answer;

    static bool isPointOnSegment(int x, int y, int A1x, int A1y, int A2x, int A2y) {
        // 当(x, y)在直线A1A2上时 检验(x, y)是否在线段A1A2上
        return (
                ((A1x == A2x) || (min(A1x, A2x) <= x && x <= max(A1x, A2x)))
                &&
                ((A1y == A2y) || (min(A1y, A2y) <= y && y <= max(A1y, A2y)))
        );
    }

    void updateAnswer(double x, double y) {
        if (answer.empty() || x < answer[0] || (fabs(x - answer[0]) < EPS && y < answer[1])) {
            answer = {x, y};
        }
    }

    vector<double> intersection(vector<int> &A1, vector<int> &A2, vector<int> &B1, vector<int> &B2) {
        int A1x = A1[0], A1y = A1[1], A2x = A2[0], A2y = A2[1];
        int B1x = B1[0], B1y = B1[1], B2x = B2[0], B2y = B2[1];

        if ((A2y - A1y) * (B2x - B1x) == (B2y - B1y) * (A2x - A1x)) { // A1A2与B1B2平行
            if ((B1x - A1x) * (A2y - A1y) == (B1y - A1y) * (A2x - A1x)) { // A1A2与B1B2共线(即B1在直线A1A2上)
                if (isPointOnSegment(B1x, B1y, A1x, A1y, A2x, A2y)) { // B1在线段A1A2上
                    updateAnswer(B1x, B1y);
                }
                if (isPointOnSegment(B2x, B2y, A1x, A1y, A2x, A2y)) { // B2在线段A1A2上
                    updateAnswer(B2x, B2y);
                }
                if (isPointOnSegment(A1x, A1y, B1x, B1y, B2x, B2y)) { // A1在线段B1B2上
                    updateAnswer(A1x, A1y);
                }
                if (isPointOnSegment(A2x, A2y, B1x, B1y, B2x, B2y)) { // A2在线段B1B2上
                    updateAnswer(A2x, A2y);
                }
            }
        } else { // A1A2与B1B2相交
            // A1x + k1(A2x - A1x) = B1x + k2(B2x - B1x)
            // A1y + k1(A2y - A1y) = B2y + k2(B2y - B1y)

            double k1 = static_cast<double>(
                                B1x * (B2y - B1y) + A1y * (B2x - B1x) - B1y * (B2x - B1x) - A1x * (B2y - B1y)
                        ) / static_cast<double>(
                                (A2x - A1x) * (B2y - B1y) - (B2x - B1x) * (A2y - A1y)
                        );
            double k2 = static_cast<double>(
                                A1x * (A2y - A1y) + B1y * (A2x - A1x) - A1y * (A2x - A1x) - B1x * (A2y - A1y)
                        ) / static_cast<double>(
                                (B2x - B1x) * (A2y - A1y) - (A2x - A1x) * (B2y - B1y)
                        );

            if (0 <= k1 && k1 <= 1 && 0 <= k2 && k2 <= 1) { // 当k1和k2都在闭区间[0, 1]内时 得到的交点坐标在线段A1A2或B1B2上
                updateAnswer(A1x + k1 * (A2x - A1x), A1y + k1 * (A2y - A1y));
            }
        }

        return answer;
    }
};
