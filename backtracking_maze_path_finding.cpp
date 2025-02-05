#include <iostream>
#include <vector>
#include <ctime>
#include <random>

class MazePathFinder 
{
public:
    MazePathFinder() = default;

    void run() {
        std::cout << "\t___________________________________________" << std::endl;
        std::cout << "\t|                                         |" << std::endl;
        std::cout << "\t|        MAZE PATH FINDING ALGORITHM      |" << std::endl;
        std::cout << "\t|_________________________________________|" << std::endl;
        std::cout << "\n\t\t[1] Create a new maze" << std::endl;
        std::cout << "\t\t[2] Generate a maze automatically" << std::endl;
        std::cout << "\t\t[0] Exit\n" << std::endl;
        std::cout << "\tChoose your option: ";
        std::cin >> this->input_choice;

        if (this->input_choice == "1")
            take_input_maze();
        else if (this->input_choice == "2")
            generate_maze();
        else
            exit(0);
    }

private:
    void findPathHepler(int i, int j,
                        const std::vector<std::vector<int>>& maze,
                        int arr_size,
                        std::vector<std::string>& ans,
                        std::string path,
                        std::vector<std::vector<int>>& visited) noexcept
    {
        // reached end of the matrix (final point)
        if (i == arr_size-1 && j == arr_size-1) {
            ans.push_back(path);
            return;
        }

        // going downwards
        // if i less then arr_size, and is not visited
        // and the next block is not 0 (not wall), we do
        if (i+1 < arr_size && !visited[i+1][j] && maze[i+1][j] == 1)
        {
            visited[i][j] = 1;
            findPathHepler(i+1, j, maze, arr_size, ans, path+'D', visited);
            visited[i][j] = 0;
        }

        // going left
        if (j-1 >= 0 && !visited[i][j-1] && maze[i][j-1] == 1)
        {
            visited[i][j] = 1;
            findPathHepler(i, j-1, maze, arr_size, ans, path+'L', visited);
            visited[i][j] = 0;
        }

        // going right
        if (j+1 < arr_size && !visited[i][j+1] && maze[i][j+1] == 1)
        {
            visited[i][j] = 1;
            findPathHepler(i, j+1, maze, arr_size, ans, path+'R', visited);
            visited[i][j] = 0;
        }

        // going upwards
        if (i-1 >= 0 && !visited[i-1][j] && maze[i-1][j] == 1)
        {
            visited[i][j] = 1;
            findPathHepler(i-1, j, maze, arr_size, ans, path+'U', visited);
            visited[i][j] = 0;
        }
    }

    [[nodiscard]] 
    const std::vector<std::string> findPath(const std::vector<std::vector<int>>& maze, const int& arr_size)
    {
        std::vector<std::string> ans;
        std::vector<std::vector<int>> visited(arr_size, std::vector<int>(arr_size, 0));

        // we are starting the maze path finding from here
        if (maze[0][0] == 1)
            // findPathHepler(x_axis,y_axis,maze_array,dimensions,result_paths,visited_paths)
            findPathHepler(0,0,maze,arr_size,ans,"",visited);

        return ans;
    }

    void maze_visualization(std::vector<std::string>& result_paths, const int& n)
    {
        int i = 0; // used for displaying the path number
        std::cout << "\n All individual paths: \n" << std::endl;
        for (auto strs : result_paths)
        {
            std::cout << " Path " << i+1 << ": " << result_paths[i] << "\n\n";
            std::vector<std::vector<char>> DisplayMaze(n, std::vector<char>(n, '#'));

            int vertical=0,horizontal=0;
            DisplayMaze[horizontal][vertical] = 'S';

            for (auto j : strs) {
                if (j == 'D')
                    vertical++;
                else if (j == 'R')
                    horizontal++;
                else if (j == 'U')
                    vertical--;
                else if (j == 'L')
                    horizontal--;

                DisplayMaze[vertical][horizontal] = '.';
            }

            DisplayMaze[n-1][n-1] = 'E';

            for (int i=0; i < n; i++)
            {
                for (int j=0; j < n; j++)
                    std::cout << " " << DisplayMaze[i][j] << " ";
                std::cout << "\n";
            }
            std::cout << "\n";
            i++;
        }

        int shortest_path = result_paths[0].size(), short_idx = 0;
        for (size_t j = 0; j < result_paths.size(); j++)
        {
            if (static_cast<int>(result_paths[j].size()) < shortest_path) {
                shortest_path = result_paths[j].size();
                short_idx = j;
            }
        }

        std::cout << "\n 'S' = starting point\n 'E' = end point\n '#' = Wall\n '.' = Avalilable Route/Path\n\n";
        std::cout << " Total Paths: " << result_paths.size() << "\n";
        std::cout << " Shortest path is Path no. " << short_idx+1 << " (" << shortest_path << " steps total)\n\n\n";

    }

    // maze is processed here
    void main_func_helper(std::vector<std::vector<int>>& maze, int arr_size)
    {
        std::vector<std::string> result = findPath(maze, arr_size);
        if (result.size() == 0) {
            std::cout << " No path exists to the end point!\n";
            return;
        }

        maze_visualization(result, arr_size);

        std::string input;
        do
        {
            std::cout<<" enter 0 to exit....  ";
            std::cin>> input;
        }
        while (input != "0");
    }

    void take_input_maze()
    {

#if __linux__
        system("clear");
#elif _WIN32
        system("cls");
#endif

        int n;
        std::cout << "\n Enter Maze Dimension: \n ";
        std::cin >> n;

        std::vector<std::vector<int>> maze(n, std::vector<int>(n,0));
        std::cout << "\n Enter the values for " << n << "x" << n << " maze: \n ";
        for (int i=0; i < n; i++) {
            for (int j=0; j<n; j++) {
                std::cin >> maze[i][j];
            }
        }

        std::cout << "\n Visualization of input maze: "<< std::endl;
        for(size_t i=0;i<maze.size(); i++) 
        {
            for (size_t j=0;j<maze[i].size(); j++) 
            {
                maze[i][j] == 0 ? std::cout << " # "
                                : std::cout << " . ";
            }
            std::cout<< "\n";
        }
        std::cout << "\n";

        main_func_helper(maze, n);
    }

    void generate_maze()
    {

#if __linux__
        system("clear");
#elif _WIN32
        system("cls");
#endif

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, this->preloaded_mazes.size());
        
        int rand_idx = dist(gen);
        std::vector<std::vector<int>> gen_maze = this->preloaded_mazes[rand_idx];

        std::cout << " auto generated maze: " << std::endl;
        for(size_t i = 0; i < gen_maze.size(); i++)
        {
            for (size_t j = 0; j < gen_maze[i].size(); j++)
            {
                gen_maze[i][j] == 0 ? std::cout << " # "
                                    : std::cout << " . ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";

        main_func_helper(gen_maze, gen_maze.size());
    }

private:
    // we are pre-loading different types of mazes instead of generting instantly
    const std::vector<std::vector<std::vector<int>>> preloaded_mazes = {
        {{1,0,0,0},{1,1,0,1},{1,1,0,0},{0,1,1,1}},
        {{1,0,1,1,1},{1,1,1,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,1,1,1,1}},
        {{1,0,0,0,1,1},{1,1,1,0,1,0},{0,0,1,1,1,0},{0,0,0,0,1,1},{1,1,1,1,1,0},{0,0,0,0,1,1}},
        {{1,1,0,0,1,0,1},{0,1,0,1,1,1,1},{1,1,0,1,0,0,1},{0,1,0,1,0,0,1},{1,1,1,1,0,1,1},{1,0,0,0,0,0,1},{1,1,1,1,1,1,1}},
    };

    std::string input_choice;
};

int main()
{
    MazePathFinder maze{};
    maze.run();

    return 0;
}
