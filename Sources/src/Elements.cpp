/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing,
 *  software distributed under the License is distributed on an
 *  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 *  KIND, either express or implied.  See the License for the
 *  specific language governing permissions and limitations
 * under the License.
 */

/**
 * File: Elements.cpp
 * Creation: 2015-02-13 07:39
 * Louis Solofrizzo <louis@ne02ptzero.me>
 */

# include "../inc/Elements.hpp"

/**
 * Basic constructor
 */
Elements::Elements(int id) : _id(id) {
	return ;
}

/**
 * Basic deconstructor
 */
Elements::~Elements(void) {
	return ;
}

void	Elements::addAttribute(std::string name, std::string value) {
	this->_attributes[name] = value;
}

std::string	Elements::getAttribute(std::string name) {
	return this->_attributes[name];
}
