#pragma once

#include <ge211_geometry.hxx>

/// We will represent positions as GE211 `Posn<int>`s, which we alias
/// with the type name `Position`. This is a struct that could be
/// defined like so:
///
///   struct Position
///   {
///       int x;   // pixel distance from left edge of window
///       int y;   // pixel distance from top edge of window
///   };
using Position = ge211::Posn<int>;

struct Food
{
    // Member function

    /// Constructs food at give position with value
    Food(Position posn, int to_value);

    // Member variables

    /// Position of food
    Position pos;

    /// Value of food
    int value;
};

