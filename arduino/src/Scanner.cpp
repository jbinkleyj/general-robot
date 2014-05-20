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

#include <Arduino.h>
#include "Scanner.h"

Scanner::Scanner(Servo * motor, HcSr04 * sensor) {
    _motor = motor;
    _sensor = sensor;

    _current_position = CENTER_POSITION;
    _current_orientation = RIGHT_ORIENTATION;
}


ScanResponse Scanner::scan() {
    ScanResponse * response = new ScanResponse();
   
    _motor->write(_current_position);
    delay(150); 
    long distance = _sensor->read_distance();
    response->set_distance(distance);
    response->set_position(_current_position);

    if (_current_orientation == RIGHT_ORIENTATION) {
        switch(_current_position) {
            case LEFT_POSITION: 
                _current_position = CENTER_POSITION;
                break;
            case CENTER_POSITION:
                _current_position = RIGHT_POSITION;
                _current_orientation = LEFT_ORIENTATION;
                break;
        }
    } else if (_current_orientation == LEFT_ORIENTATION) {
        switch(_current_position) {
            case RIGHT_POSITION:
                _current_position = CENTER_POSITION;
                break;
            case CENTER_POSITION:
                _current_position = LEFT_POSITION;
                _current_orientation = RIGHT_ORIENTATION;
                break;
        }
    }

    return *response;

}
