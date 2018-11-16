#pragma once




class NoMove
{

public:

    NoMove() = default;

    NoMove(NoMove&&) = delete;

    NoMove& operator=(NoMove&&) = delete;

};


