// Subesh
const button = document.getElementById("play");
const score = document.getElementById("score");
const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");
const mod = (m, val) => {
  while (val < 0) {
    val += m;
  }
  return val % m;
};

var state = {
  gameover: true,
  direction: 2,
  snake: [
    { x: 10, y: 10, direction: 2 },
    { x: 10, y: 20, direction: 2 },
    { x: 10, y: 30, direction: 2 }
  ],
  food: { x: 0, y: 0 },
  score: 0
};

/*   a*/
function generateFood() {
  const snake = state.snake;
  let x = Math.floor(Math.random() * 25) * 10;
  let y = Math.floor(Math.random() * 25) * 10;

  while (snake.some(part => part.x === x && part.y === y)) {
    x = Math.floor(Math.random() * 25) * 10;
    y = Math.floor(Math.random() * 25) * 10;
  }
  state.food = { x, y };
}

function addPart() {
  let snake = state.snake;
  let { x, y, direction } = snake[snake.length - 1];
  switch (direction) {
    case 1:
      y = mod(250, y - 10);
      break;
    case -1:
      y = mod(250, y + 10);
      break;
    case -2:
      x = mod(250, x + 10);
      break;
    case 2:
      x = mod(250, x - 10);
      break;
  }
  state.snake.push({ x, y, direction });
}

function eatFood() {
  let { x, y } = state.snake[0];
  let { x: fx, y: fy } = state.food;

  if (x == fx && y == fy) {
    state.score++;
    score.innerHTML = "Score: " + state.score;
    addPart();
    generateFood();
  }
}
function checkGameOver() {
  const head = state.snake[0];
  return state.snake.some(
    (part, i) => i !== 0 && head.x === part.x && head.y === part.y
  );
}

document.addEventListener("keydown", event => {
  if (/Arrow/gi.test(event.key)) event.preventDefault();
  let direction = 0;
  switch (event.key) {
    case "ArrowDown":
      direction = 1;
      break;
    case "ArrowUp":
      direction = -1;
      break;
    case "ArrowLeft":
      direction = -2;
      break;
    case "ArrowRight":
      direction = 2;
      break;
  }
  if (
    direction &&
    state.direction == state.snake[0].direction &&
    state.direction != -direction
  ) {
    state.direction = direction;
  }
});

function drawSnakePart(x, y, head = false) {
  ctx.fillStyle = head ? "green" : "white";
  ctx.fillRect(x, y, 10, 10);
}
function drawSnake(snake) {
  for (let i = snake.length - 1; i >= 0; --i) {
    drawSnakePart(snake[i].x, snake[i].y, i === 0);
  }
}
function drawFood() {
  let x = state.food.x;
  let y = state.food.y;
  ctx.beginPath();
  ctx.fillStyle = "red";
  ctx.arc(x + 5, y + 5, 5, 0, 2 * Math.PI);
  ctx.stroke();
  ctx.fill();
}
function drawBackground() {
  ctx.fillStyle = "tan";
  ctx.fillRect(0, 0, 250, 250);
}

var start = 0;
function draw(timestamp) {
  start++;
  if (timestamp - start > 1000 / 10) {
    if (checkGameOver()) {
      state.gameover = true;
      return;
    }
    let snake = state.snake;
    let direction = state.direction;
    let x = snake[0].x;
    let y = snake[0].y;
    switch (direction) {
      case 1:
        y = mod(250, y + 10);
        break;
      case -1:
        y = mod(250, y - 10);
        break;
      case -2:
        x = mod(250, x - 10);
        break;
      case 2:
        x = mod(250, x + 10);
        break;
    }
    const newSnake = [{ x, y, direction }];
    const snakeLength = snake.length;
    for (let i = 1; i < snakeLength; ++i) {
      newSnake.push({ ...snake[i - 1] });
    }
    state.snake = newSnake;
    drawBackground();
    drawFood();
    drawSnake(newSnake);
    eatFood();
    start = timestamp;
  }
  if (!state.gameover) window.requestAnimationFrame(draw);
}

play.onclick = () => {
  if (state.gameover) {
    state = {
      gameover: false,
      direction: 2,
      snake: [
        { x: 10, y: 10, direction: 2 },
        { x: 10, y: 20, direction: 2 },
        { x: 10, y: 30, direction: 2 }
      ],
      food: { x: 0, y: 0 },
      score: 0
    };
    score.innerHTML = "Score: " + 0;
    generateFood();
    window.requestAnimationFrame(draw);
  }
};
