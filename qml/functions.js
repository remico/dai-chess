function rowByCell(cell) { return (cell % 8 ? Math.floor(cell / 8) + 1 : Math.floor(cell / 8)) - 1; }
function columnByCell(cell) { return (cell % 8 ? cell % 8 : 8) - 1; }
function cellByPosition(x, y) { return (Math.floor(x / cellSize) + 1) + Math.floor(y / cellSize) * 8; }
