#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <unistd.h>
#include <sstream>

using namespace std;

int intdiv_round(int a, int b) {
    return ((2*a / b) + 1) / 2;
}

pair <int, int> last_bufsize {-1, -1};

void write_buffer(const vector <string>& buf) {
    stringstream ss;
    if (last_bufsize.first < (int)buf.size() || last_bufsize.second < (int)buf.at(0).size()) {
        last_bufsize = {(int)buf.size(), (int)buf.at(0).size()};
        ss << "\x1b[3J\x1b[H\x1b[J";
    }

    ss << "\x1b[0;0H";

    for (const auto& i : buf) {
        ss << i << '\n';
    }
    cout << ss.str();
    cout.flush();
}

template <typename A, typename B>
ostream& operator<< (ostream& out, const pair <A, B>& pr) {
    out << "(" << pr.first << ", " << pr.second << ")";
    return out;
}

void draw_line(vector <string>& buf, pair <int, int> v1, pair <int, int> v2, char ch) {
    int dx = v2.first - v1.first;
    int dy = v2.second - v1.second;

    if (dy == 0) {
        for (int i = min(v1.first, v2.first); i <= max(v1.first, v2.first); ++i) {
            buf.at(v1.second).at(i) = ch;
        }
        return;
    } else if (dx == 0) {
        for (int i = min(v1.second, v2.second); i <= max(v1.second, v2.second); ++i) {
            buf.at(i).at(v1.first) = ch;
        }
        return;
    }

    if (abs(dx) > abs(dy)) {
        if (v2.first < v1.first) {
            swap(v1, v2);
            dx = -dx;
            dy = -dy;
        }
        int bx = v1.first, by = v1.second;
        for (int i = 0; i <= dx; ++i) {
            int x = bx + i;
            int y = by + intdiv_round(i * dy, dx);
            buf.at(y).at(x) = ch;
        }
    } else {
        if (v2.second < v1.second) {
            swap(v1, v2);
            dx = -dx;
            dy = -dy;
        }
        int bx = v1.first, by = v1.second;
        for (int i = 0; i <= dy; ++i) {
            int y = by + i;
            int x = bx + intdiv_round(i * dx, dy);
            buf.at(y).at(x) = ch;
        }
    }
}

void fill_tri(vector <string>& buf, pair <int, int> v1, pair <int, int> v2, pair <int, int> v3, char ch) {
    int min_x = min(min(v1.first, v2.first), v3.first);
    int min_y = min(min(v1.second, v2.second), v3.second);
    int max_x = max(max(v1.first, v2.first), v3.first);
    int max_y = max(max(v1.second, v2.second), v3.second);

    int dx = max_x - min_x + 1;
    int dy = max_y - min_y + 1;
    vector <string> tmp(dy, string(dx, '?'));

    v1.first -= min_x;
    v2.first -= min_x;
    v3.first -= min_x;
    v1.second -= min_y;
    v2.second -= min_y;
    v3.second -= min_y;

    draw_line(tmp, v1, v2, 'y');
    draw_line(tmp, v1, v3, 'y');
    draw_line(tmp, v2, v3, 'y');
    
    for (auto& i : tmp) {
        for (int j = 0; j < (int)i.length() && i.at(j) != 'y'; ++j) {
            i.at(j) = 'n';
        }
        for (int j = (int)i.length() - 1; j >= 0 && i.at(j) != 'y'; --j) {
            i.at(j) = 'n';
        }
    }
    
    for (int i = 0; i < dy; ++i) {
        for (int j = 0; j < dx; ++j) {
            if (tmp.at(i).at(j) != 'n') {
                buf.at(i + min_y).at(j + min_x) = ch;
            }
        }
    }
}

int main() {
    cout.sync_with_stdio(false);
    const int width = 120, height = 40;
    auto get_delta = [](double angle) {
        int dx = cos(angle) * 30;
        int dy = sin(angle) * 15;
        return make_pair (60 + dx, 20 + dy);
    };
    
    double ang = 0;
    while (true) {
        vector <string> buf(height, string(width, '.'));
        fill_tri(buf, get_delta(ang), get_delta(ang + 2 * M_PI / 3), get_delta(ang - 2 * M_PI / 3), '=');
        write_buffer(buf);
        usleep(100'000);
        ang += 0.1;
    }
}
