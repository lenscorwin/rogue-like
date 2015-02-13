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
 * File: Game.cpp
 * Creation: 2015-02-13 07:20
 * Louis Solofrizzo <louis@ne02ptzero.me>
 */

#include "../inc/Game.hpp"


/**
 * Basic constructor, set the window to default value
 * (http://docs.angel2d.com/class_world.html#ae5d7e8d20d3e6fc93785ab2014ac0c13)
 */
Game::Game(void) {
	theWorld.Initialize(1024, 768, NAME);
	//this->elements = new Elements();
	this->maps = new Maps("Maps/");
	return ;
}

/**
 * Constructor with custom window width & height
 * @param: width (unsigned int)
 * @param: heigh (unsigned int)
 */
Game::Game(unsigned int width, unsigned int height) {
	theWorld.Initialize(width, height, NAME);
	//this->elements = new Elements();
	this->maps = new Maps("Maps/");
}

/**
 * Deconstructor
 */
Game::~Game(void) {
	//delete this->elements;
	return ;
}

/**
 * Add a grid to the world (DEBUG)
 */
void	Game::grid(void) {
	theWorld.Add(new GridActor(), -1);
}

/**
 * Let's start the game
 */
void	Game::start(void) {
	theWorld.StartGame();
}

/**
 * Read the maps
 */
void	Game::readMaps(void) {
	this->maps->readMaps();
}
