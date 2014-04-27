/*
   Generic Robot with obstacle avoidance capabilities
   Copyright (C) 2014  Joao Salavisa (joao.salavisa@gmail.com)

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

class ScanResponse {
    private:
        int _position;
        long _distance;

    public:
        ScanResponse() {};
        void set_position(int position) { _position = position; };
        void set_distance(long distance) {_distance = distance; };

        long get_distance() { return _distance; };
        long get_position() { return _position; };
};
