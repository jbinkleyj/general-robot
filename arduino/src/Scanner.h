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

#ifndef SCANNER_H
#define SCANNER_H

#include <Servo.h>
#include "HcSr04.h"
#include "ScanResponse.h"

#define LEFT_POSITION        20
#define CENTER_POSITION      90
#define RIGHT_POSITION      160

#define RIGHT_ORIENTATION     -1
#define LEFT_ORIENTATION       1

class Scanner {

    private:
        // fields
        Servo * _motor;
        HcSr04 * _sensor;
       
        int _current_position;
        int _current_orientation;
        // methods
        void next_position();
        long read_distance();
        
         
    public:
        Scanner(Servo * motor, HcSr04 * sensor);
        ScanResponse scan();

};
#endif SCANNER_H
