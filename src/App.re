type state = {
  tempoMin: int,
  tempoSec: int,
};

type actionType =
  | ChangeTempoMin
  | ChangeTempoSec
;

type action = {
  type_: actionType,
  payload: int,
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer((state, action) =>
    switch (action.type_) {
    | ChangeTempoMin => {...state, tempoMin: action.payload}
    | ChangeTempoSec => {...state, tempoSec: action.payload}
    },
    {
      tempoMin: 0,
      tempoSec: 0,
    }
  );

  <div>
    <label>
      {ReasonReact.string("Tempo")}

      <input onChange={event => {
        let value = ReactEvent.Form.target(event)##value
        dispatch({
          type_: ChangeTempoMin,
          payload: try (int_of_string(value)) {
          | Failure("int_of_string") => 0
          },
        })
      }} value={Js.Int.toString(state.tempoMin)} />

      {ReasonReact.string(":")}

      <input onChange={event => {
        let value = ReactEvent.Form.target(event)##value
        dispatch({
          type_: ChangeTempoSec,
          payload: try (int_of_string(value)) {
          | Failure("int_of_string") => 0
          },
        })
      }} value={Js.Int.toString(state.tempoSec)} />
    </label>
    <div>
      {ReasonReact.string("Speed " ++ Js.Float.toString(60. /. (float_of_int(state.tempoMin) +. float_of_int(state.tempoSec) /. 60.)) ++ " km/h")}
    </div>
  </div>;
};
