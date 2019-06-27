type state = {
  tempoMin: int,
  tempoSec: int,
  speed: float,
};

type action =
  | ChangeTempoMin(int)
  | ChangeTempoSec(int)
  | ChangeSpeed(float)
;

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer((state, action) =>
    switch (action) {
    | ChangeTempoMin(min) =>
      {
        ...state,
        tempoMin: min,
        speed: 60. /. (float(min) +. float(state.tempoSec) /. 60.),
      }
    | ChangeTempoSec(sec) =>
      {
        ...state,
        tempoSec: sec,
        speed: 60. /. (float(state.tempoMin) +. float(sec) /. 60.),
      }
    | ChangeSpeed(speed) =>
      let (fractional, integral) = modf(60. /. speed);
      {
        speed: speed,
        tempoMin: truncate(integral),
        tempoSec: truncate(fractional *. 60. +. 0.5),
      }
    },
    {
      tempoMin: 0,
      tempoSec: 0,
      speed: 0.,
    }
  );

  <div>
    <h1>{ReasonReact.string("Runcalc")}</h1>

    <h2>{ReasonReact.string("Tempo")}</h2>
    <div className="form-group">
      <label>
      {ReasonReact.string("min")}
      <input className="form-control" onChange={event => {
        let value = ReactEvent.Form.target(event)##value
        dispatch(ChangeTempoMin(
          try (int_of_string(value)) {
          | Failure("int_of_string") => 0
          }
        ))
      }} value={Js.Int.toString(state.tempoMin)} />
    </label>
    </div>

    {ReasonReact.string(":")}

    <label>
      {ReasonReact.string("sec")}
      <input className="form-control" onChange={event => {
        let value = ReactEvent.Form.target(event)##value
        dispatch(ChangeTempoSec(
          try (int_of_string(value)) {
          | Failure("int_of_string") => 0
          }
        ))
      }} value={Js.Int.toString(state.tempoSec)} />
    </label>

    <h2>{ReasonReact.string("Speed")}</h2>
    <div>
      <label>
        <input className="form-control" onChange={event => {
          let value = ReactEvent.Form.target(event)##value
          dispatch(ChangeSpeed(
            try (float_of_string(value)) {
            | Failure("int_of_string") => 0.
            }
          ))
        }} value={Js.Float.toFixedWithPrecision(state.speed, ~digits = 2)} />
      </label>

      {ReasonReact.string("km/h")}
    </div>
  </div>;
};
