#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    Controller(Model&);

    void on_key(ge211::Key) override;

    void on_mouse_up(ge211::Mouse_button, ge211::Posn<int>) override;

    void on_frame(double dt) override;

    /// The GE211 framework calls this to find out how big to make the
    /// window. The implementation in controller.cxx delegates this to
    /// view.initial_window_dimensions(), since the view show know how
    /// big it wants the window to be.
    ge211::Dims<int> initial_window_dimensions() const override;

protected:
    /// The GE211 framework calls this at regular intervals to ask the
    /// game what should appear on the screen. It’s given a reference to
    /// an empty set of sprites (corresponding to painting the scene
    /// from scratch), to which it adds sprites at various positions,
    /// which the framework then renders to the screen. The
    /// implementation in controller.cxx delegates to view.draw(), since
    /// visuals are the view’s job.
    void draw(ge211::Sprite_set& set) override;

private:
    //
    // MEMBER VARIABLES
    //

    /// This is a reference to the model. It means that the controller
    /// doesn't own the model but has access to it. Thus, the client of
    /// the controller (game.cxx) must create a `Model` first and
    /// then pass that by reference to the `Controller` constructor.
    Model& model_;

    /// This is the view, which contains the game’s data and code for
    /// displaying the state of the model to the screen.
    View view_;
};
