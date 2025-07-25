import "../index.css";
import whitePawn from "../assets/whitePawn.svg";
import whiteKnight from "../assets/whiteKnight.svg";
import whiteBishop from "../assets/whiteBishop.svg";
import whiteRook from "../assets/whiteRook.svg";
import whiteQueen from "../assets/whiteQueen.svg";
import whiteKing from "../assets/whiteKing.svg";
import blackPawn from "../assets/blackPawn.svg";
import blackKnight from "../assets/blackKnight.svg";
import blackBishop from "../assets/blackBishop.svg";
import blackRook from "../assets/blackRook.svg";
import blackQueen from "../assets/blackQueen.svg";
import blackKing from "../assets/blackKing.svg";

export default function Square(props) {
  function lightSquare() {
    if (props.row % 2 == 0 && props.col % 2 == 0) {
      return true;
    } else if (props.row % 2 == 1 && props.col % 2 == 1) {
      return true;
    } else {
      return false;
    }
  }

  function getImage() {
    if (props.value.iswhite) {
      switch (props.value.type) {
        case "p":
          return whitePawn;
        case "n":
          return whiteKnight;
        case "b":
          return whiteBishop;
        case "r":
          return whiteRook;
        case "q":
          return whiteQueen;
        case "k":
          return whiteKing;
      }
    } else {
      switch (props.value.type) {
        case "p":
          return blackPawn;
        case "n":
          return blackKnight;
        case "b":
          return blackBishop;
        case "r":
          return blackRook;
        case "q":
          return blackQueen;
        case "k":
          return blackKing;
      }
    }
  }

  function getBackgroundColor() {
    if (props.isSelected) {
      return "#e6c95f";
    } else if (lightSquare()) {
      return "#F0D9B5";
    } else {
      return "#B58863";
    }
  }

  const backgroundColor = getBackgroundColor();
  const squareStyles = { backgroundColor: backgroundColor };

  return (
    <section
      className="squareElement"
      style={squareStyles}
      onClick={props.handleClick}
    >
      {props.value != null && <img className="pieceImg" src={getImage()} />}
      {props.isPossibleMove && <div className="lightCircle"></div>}
    </section>
  );
}
