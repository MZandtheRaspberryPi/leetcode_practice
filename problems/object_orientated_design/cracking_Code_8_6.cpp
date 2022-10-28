/*
Implement jigsaw puzzle. design datastructures and explain
algo to solve puzzle. assume have fitsWith method that passed 2 pieces and returns true if
pieces belong together.

do jigsaw pieces have four sides like most?

assume that they do.

edge
piece 
puzzle 

edge  types, outer, inner, flat
piece located in row/col, 4 edges
absolute pos, 14, 3, in puzzle
relative, next to this other piece. will use this.

*/

#include <vector>

enum EdgeType
{
	INNER,
	OUTER,
	FLAT	
};

class Piece;
class Edge;

class Piece
{
	public:
		Edge* edges[4];
		bool isCorner();
	
};

class Edge
{
	
	public:
		// see algo bit, return true if 2 pieces should be attached to each other
		bool fitsWith(Edge edge);
		
	private:
	  EdgeType type;
		Piece parent;
		int index; //index into piece.edges
		Edge* attached_to; //relative position

};

class Puzzle
{
	std::vector<Piece> pieces;
	std::vector<std::vector<Piece>> solution;
	
	std::vector<Edge> inners;
	std::vector<Edge> outers;
	std::vector<Edge> flats;
	
	std::vector<Piece> corners;
	
	
	public:	
	
		void sort()
		{
			// start with corners and edges, go through to find them, and while at it group pieces by edge types
			for (Piece p : pieces)
			{
				// if piece has 2 flat edges, add to corners.
				// for each edge in p.edges, if edge inner add to inners. if edge outer, add to outers.
			}
			
		}
		void solve()
		{
			// pick arbitrary corner to start with. find open edge and try to match to open piece.
			// to match, when finds, attatch the edge, remove edge from list of open edges
			// find next open edge
			
			// next open edge should be directly opposite current edge, if available.
			// if not, can move on
			// so spiral like fashion, outside to inside.
			// algo moves straight line, when reach edge of first edge, takes turn, continueing.
			// pick any corner to start
			// Edge currentEdge = getExposedEdge(corners[0])
			Edge* currentEdge = corners[0].edges[0];
			
		}
	
};


int main()
{
	
}
