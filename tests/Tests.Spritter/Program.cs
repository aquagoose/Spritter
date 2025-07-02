using Spritter;
using Tests.Spritter;

GameInfo info = new("Tests.Spritter");

using TestGame game = new TestGame();
game.Run(info);