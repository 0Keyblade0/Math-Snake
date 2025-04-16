#pragma once

#include "food.hxx"

#include <iostream>

#include <vector>

#include <ge211_geometry.hxx>

using Temp_position = ge211::geometry::Posn<float>;

/// We will represent velocities as GE211 `Dims<float>`s, which we alias
/// with the type name `Velocity`. This is a struct that could be
/// defined like so:
///
///   struct Velocity
///   {
///       float width;   // horizontal rate of change (px/s)
///       float height;  // vertical rate of change (px/s)
///   };
using Velocity = ge211::Dims<double>;

/// We will represent all snake_parts as a position
using Snake_part = Position;

struct Snake {

    // Member functions

    /// Constructs a snake. Initially is only has
    /// a head - no body. Since the grid does not change the snake
    /// should spawn in the same position everytime: the center of
    /// the board
    Snake();

    /// Returns the state of the snake after `dt` seconds have passed,
    /// were it to move freely (without obstacles). Thus, the result is
    /// a new snake just like this one but whose positions have been
    /// updated based on its current velocity and the given time
    /// interval `dt`. (This is an application of the equation relating
    /// distance to velocity and time: *Δd = v ⋅ Δt*.)
    ///
    /// This function is useful because the model's algorithm for
    /// collision detection involves speculatively moving the ball and
    /// checking where it would end up, before actually moving it.
    ///
    /// This can also be used to actually move it, via assignment:
    ///
    ///    snake = snake.next();
    ///
    Snake next(double dt) const;

    /// Determines whether the snake hits the boundary
    bool hits_boundary() const;

    /// Determines whether the snake hits itself
    bool hits_self() const;

    /// Determines if the snake is at food
    bool at_food(const std::vector<Food>& foods) const;

    /// Determines which food the snake, returns
    /// position off grid if not
    Food which_food(const std::vector<Food>& foods);

    /// Makes the snake's body longer
    void longer();

    /// Makes the snake's body shorter
    void shorter();

    // Member variables

    /// The head of the snake (position)
    Snake_part head;

    Temp_position fake_head;

    /// The body of the snake
    std::vector<Snake_part> body;

    /// The velocity that the head of the snake is moving in
    Velocity velocity;

    /// Whether the snake is moving freely (true) or not (false).
    bool live;

};

/// Two Snake`s are equal if all their member variables are pairwise
/// equal.
bool operator==(Snake const&, Snake const&);

/// Inequality for `Snake`s.
bool operator!=(Snake const&, Snake const&);

/// Stream insertion (printing) for `Ball`. This can make your test
/// results easier to read.
std::ostream&
operator<<(std::ostream&, Snake const&);