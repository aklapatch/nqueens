#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctype.h>
#include <utility>
#include <vector>

typedef std::pair<int,int> queen;

bool isConflict(queen t_primary, std::stack<queen> t_q_stack, unsigned int board_size){
	std::vector<queen> queens(t_q_stack.size());
	
	//copy the stack contents to vector
	int i=0;
	while( !t_q_stack.empty() ){
		queens[ i++ ] = t_q_stack.top();
		t_q_stack.pop();
	}
	
	while( i-- > 0){
	
		if( t_primary.second == queens[i].second || t_primary.second > board_size){
			std::cout << "Queen at " << t_primary.first << "," << t_primary.second << " conflicts with queen at "; 
			std::cout << queens[i].first << "," << queens[i].second << "\n";
			return true;
		}

		int b = t_primary.first - t_primary.second;
		int b2 = queens[i].first - queens[i].second;
		int b3 = t_primary.first + (t_primary.second - board_size);
		int b4 = queens[i].first + (queens[i].second - board_size);
		// if they are the same, queens conflict
		if ( b == b2 || b3 == b4 ){
			std::cout << "Queen at " << t_primary.first << "," << t_primary.second << " conflicts with queen at "; 
			std::cout << queens[i].first << "," << queens[i].second << "\n";
			return true;
		}
	}
	return false;
}

bool shift(queen& t_in, unsigned int board_size){
	
	// if queen is on right edge of the board
	if(t_in.second >= board_size){
		
		return false;
		
	} else {
		// move the queen to the right to the next column
		++t_in.second;
	}
	// move succeeded
	return true;	
}

int main(int argc, char ** argv) {
	
	// print usage guidelines and exit if there is not a number
	if(argc < 2 || !isdigit(argv[1][0]) ){
		std::cerr << "Usage: " << argv[0] << " NumberOfRows\n";
		return 0;
	}
	// set sized based on argument
	int board_size = std::atoi(argv[1]);
	
	// exit if the input is too small
	if(board_size < 3){
		std::cerr << "Minimum size is 3. Exiting\n";
		return 0;
	}
	
	// make first stack
	std::stack<queen> queen_stack;
	unsigned int num_filled = 1;
	
	std::cout << "Pushing queen at 1,1\n";
	queen_stack.push(std::pair<int,int>(1,1));
	
	while (num_filled < board_size){
		queen add_queen = queen_stack.top();
		++add_queen.first;
		add_queen.second = 1;
		
		bool endflag = true;
		while(endflag){
			if(isConflict(add_queen, queen_stack, board_size)){
				// try a shift
				while( !shift(add_queen, board_size)  ){
					
					// pop queen to move again
					add_queen = queen_stack.top();
					queen_stack.pop();
					--num_filled;
					std::cout << "Popping queen at " << add_queen.first << "," << add_queen.second << "\n";	

				}
			} else {
				// throw non-conflict queen on the stack
				std::cout << "pushing queen at " << add_queen.first << "," << add_queen.second << "\n";
				queen_stack.push(add_queen);
				++num_filled;
				std::cout << "Number of queens = " << num_filled << "\n";
				endflag = false;
			}
		}
	}

	std::cout << "Final positions:\n";
	for(int i = 0; i < board_size; ++i){
		std::cout << queen_stack.top().first << "," << queen_stack.top().second << "\n";
		queen_stack.pop();
	}

	return 0;
}
