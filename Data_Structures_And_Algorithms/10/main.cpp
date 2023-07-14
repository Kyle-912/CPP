#include "AdjacencyList.h"
#include "Artist.h"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

void merge(std::vector<Artist> &artists, int left, int mid, int right, int sortBy) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    Artist X[n1], Y[n2];

    for (int i = 0; i < n1; i++)
    {
        X[i] = artists[left + i];
    }
    for (int j = 0; j < n2; j++)
    {
        Y[j] = artists[mid + 1 + j];
    }
    int i, j, k;
    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2)
    {
        switch (sortBy)
        {
            case 1:
                if (X[i].getArtistName() <= Y[j].getArtistName())
                {
                    artists[k] = X[i];
                    i++;
                } else
                {
                    artists[k] = Y[j];
                    j++;
                }
                k++;
                break;
            case 2:
                if (X[i].getArtistFollowers() <= Y[j].getArtistFollowers())
                {
                    artists[k] = X[i];
                    i++;
                } else
                {
                    artists[k] = Y[j];
                    j++;
                }
                k++;
                break;
            case 3:
                if (X[i].getArtistPopularity() <= Y[j].getArtistPopularity())
                {
                    artists[k] = X[i];
                    i++;
                } else
                {
                    artists[k] = Y[j];
                    j++;
                }
                k++;
                break;
        }
    }
    while (i < n1)
    {
        artists[k] = X[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        artists[k] = Y[j];
        j++;
        k++;
    }
}

std::vector<Artist> mergeSort(std::vector<Artist> &artists, int sortBy, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(artists, sortBy, left, mid);
        mergeSort(artists, sortBy, mid + 1, right);

        merge(artists, left, mid, right, sortBy);
    }
    return artists;
}

std::vector<Artist> shellSort(std::vector<Artist> &artists, const int &sortBy)
{
    return artists;
}

int main()
{

    // input parsing here:
    std::ifstream file("nodes.csv");
    std::string line;

    // get each line of the .csv file and create an artist object to add to vector
    // of artists
    std::vector<Artist> artists;
    std::unordered_map<std::string, std::string> idToArtistName;

    // first line has column descriptions
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::istringstream s(line);
        std::string column;

        // get each column in the line (6 columns)
        std::getline(s, column, ',');
        std::string spotifyID = column;
        std::getline(s, column, ',');
        std::string artistName = column;
        std::getline(s, column, ',');

        int followers;
        try
        {
            followers = (int)std::stod(column);
        } catch (const std::invalid_argument &e)
        {
            followers = 0;
        }
        std::getline(s, column, ',');

        int popularity;
        try
        {
            popularity = (int)std::stod(column);
        } catch (const std::invalid_argument &e)
        {
            popularity = 0;
        }
        std::getline(s, column, ']');
        std::string genreList = column;

        // remove bracket, quotations
        genreList.erase(std::remove(genreList.begin(), genreList.end(), '['), genreList.end());
        genreList.erase(std::remove(genreList.begin(), genreList.end(), ']'), genreList.end());
        genreList.erase(std::remove(genreList.begin(), genreList.end(), '\"'), genreList.end());
        genreList.erase(std::remove(genreList.begin(), genreList.end(), '\''), genreList.end());

        // clean up data
        artistName.erase(std::remove(artistName.begin(), artistName.end(), '['), artistName.end());
        artistName.erase(std::remove(artistName.begin(), artistName.end(), ']'), artistName.end());
        artistName.erase(std::remove(artistName.begin(), artistName.end(), '\"'), artistName.end());
        artistName.erase(std::remove(artistName.begin(), artistName.end(), '\''), artistName.end());

        std::istringstream iss(genreList);
        std::string element;

        // add to vector
        std::vector<std::string> genres;
        while (std::getline(iss, element, ','))
        {
            genres.push_back(element);
        }

        std::getline(s, column);

        // create artist
        Artist newArtist(spotifyID, artistName, followers, popularity, genres);
        artists.push_back(newArtist);

        // place id --> name in map
        idToArtistName[spotifyID] = artistName;
    }

    // I made a basic graph structure, and added more functions like finding the
    // shortest distance between two artists using breadth first search

    // below are some functions I made that can be implemented into the menu in
    // various ways

    // also since our project is about finding popular artists by genre, we can
    // make functions for the graph to find who is the most popular to collab
    // with, as well as recommend other artists related to an artist based off
    // their adjacent vertices (collabs)!

    // graph to store artist connections
    AdjacencyList graph;

    // graph input parsing here:
    std::ifstream edgeFile("edges.csv");
    std::string edgeLine;

    while (std::getline(edgeFile, edgeLine))
    {
        std::istringstream stream(edgeLine);
        std::string edgeColumn;

        // get each column in the line (2 columns)
        std::getline(stream, edgeColumn, ',');
        std::string artist1Id = edgeColumn;
        std::getline(stream, edgeColumn);
        std::string artist2Id = edgeColumn;

        std::string artist1Name = idToArtistName[artist1Id];
        std::string artist2Name = idToArtistName[artist2Id];

        graph.addConnection(artist1Name, artist2Name);
    }

    // menu here:

    // welcome message
    std::cout << "_______________________________________________________________"
                 "____________"
              << std::endl;
    std::cout << " _    _      _                             _               "
              << std::endl;
    std::cout << "| |  | |    | |                           | |               "
              << std::endl;
    std::cout << "| |  | | ___| | ___ ___  _ __ ___   ___   | |_ ___          "
              << std::endl;
    std::cout
            << "| |/\\| |/ _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\  | __/ _ \\         "
            << std::endl;
    std::cout << "\\  /\\  /  __/ | (_| (_) | | | | | |  __/  | || (_) |        "
              << std::endl;
    std::cout
            << " \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|   \\__\\___/         "
            << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << " _____             _   _  __         _____            _   _ "
              << std::endl;
    std::cout << "/  ___|           | | (_)/ _|       /  ___|          | | | |"
              << std::endl;
    std::cout << "\\ `--. _ __   ___ | |_ _| |_ _   _  \\ `--.  ___  _ __| |_| |"
              << std::endl;
    std::cout
            << " `--. \\ '_ \\ / _ \\| __| |  _| | | |  `--. \\/ _ \\| '__| __| |"
            << std::endl;
    std::cout << "/\\__/ / |_) | (_) | |_| | | | |_| | /\\__/ / (_) | |  | |_|_|"
              << std::endl;
    std::cout
            << "\\____/| .__/ \\___/ \\__|_|_|  \\__, | \\____/ \\___/|_|   \\__(_)"
            << std::endl;
    std::cout << "      | |                     __/ |                         "
              << std::endl;
    std::cout << "      |_|                    |___/                          "
              << std::endl;
    std::cout << "_______________________________________________________________"
                 "____________"
              << std::endl
              << std::endl;

    // user input choice
    int choice = 0;

    while (choice != 4)
    {
        // print choices
        std::cout << "1. Explore collabs between artists" << std::endl;
        std::cout << "2. Explore a genre" << std::endl;
        std::cout << "3. Explore an artist" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cin >> choice;

        switch (choice)
        {
            case 1:{
                // choice 1 -- collabs
                std::cout << "Explore collabs selected." << std::endl;
                std::cout << "1. See if two artists have a collab" << std::endl;
                std::cout << "2. See the number of collabs an artist has" << std::endl;
                std::cout << "3. See the list of collabs an artist has" << std::endl;
                std::cout << "4. Find the path between two artists" << std::endl;
                int collabType;
                std::cin >> collabType;
                // Select search (print time elapsed for each search to compare as well as
                // the path distance and the path itself -- there are examples of this
                // below) BFS DFS
                break;}
            case 2:{
                // choice 2
                std::cout << "Which genre?" << std::endl;
                std::string userGenre; //it may be easier to select from a predetermined list
                std::cin >> userGenre;
                std::cout << "How would you like to sort the artists in this genre?" << std::endl;
                std::cout << "1. Name" << std::endl;
                std::cout << "2. Followers" << std::endl;
                std::cout << "3. Popularity" << std::endl;
                std::cout << "4. Number of Collabs" << std::endl;
                int sortBy;
                std::cin >> sortBy;

                if(sortBy != 4)
                {
                    std::cout << "Choose a sort:" << std::endl;
                    std::cout << "1. Merge Sort" << std::endl;
                    std::cout << "2. Shell Sort" << std::endl;
                    int sortType;
                    std::cin >> sortType;

                    if(sortType == 1)
                    {
                        // merge sorting the artists by user inputted sort type
                        std::chrono::steady_clock::time_point mergeBegin = std::chrono::steady_clock::now();
                        std::vector<Artist> mergeSortedArtists = mergeSort(artists, sortBy, 0, artists.size() - 1);
                        std::chrono::steady_clock::time_point mergeEnd = std::chrono::steady_clock::now();
                        std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::nanoseconds>(mergeEnd - mergeBegin).count() << " ns" << std::endl;
                    } else
                    {
                        // shell sorting the artists by user inputted sort type
                        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
                        std::vector<Artist> shellSortedArtists = shellSort(artists, sortBy);
                        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

                        std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ns" << std::endl;
                    }
                }

                // 4. Number of collabs

                std::vector<std::string> artistsGenre;

                for (auto &artist : artists)
                {
                    // if artist has user inputted genre in their genres, add them to the
                    // vector
                    if (std::find(artist.getArtistGenres().begin(), artist.getArtistGenres().end(), userGenre) != artist.getArtistGenres().end())
                    {
                        artistsGenre.push_back(artist.getArtistName());
                    }
                }

                std::cout << std::endl << std::endl << "Most popular artist(s) in the " << userGenre << " genre by # of collabs: " << std::endl;
                std::list<std::string> popularArtists = graph.mostPopularByGenre(artistsGenre);
                int i = 0;
                for (auto &artist : popularArtists)
                {
                    std::cout << i << ". " << artist << std::endl;
                    i++;
                }
                break;}
            case 3:
                // choice 3
                std::cout << "What artist?" << std::endl;
                std::string artistName;
                std::cin >> artistName;
                // print
                // # of collabs
                // collab list
                // popularity score
                // follower count
                break;
        }
        // choice 4
        // exit
    }

    // TODO:EXAMPLES OF FUNCTIONS

    // finds if two artists in the graph have a collab
    /*bool collab = graph.haveCollab("Taylor Swift", "Chris Stapleton");
    std::cout << "Taylor Swift and Chris Stapleton: ";

    if (collab)
    {
        std::cout << "These artists have a collab." << std::endl;
    } else
    {
        std::cout << "These artists don't have a collab" << std::endl;
    }

    // finds how many collabs an artist has
    std::cout << "Taylor Swift has " << graph.numberOfCollabs("Taylor Swift") << " collabs!" << std::endl;

    // who are the collabs with?
    std::cout << "Taylor Swift has collabs with: " << std::endl;
    std::vector<std::string> taylorCollabs = graph.collabsList("Taylor Swift");

    for (auto &artist : taylorCollabs)
    {
        std::cout << artist << std::endl;
    }

    // path between artists BFS
    std::list<std::string> path = graph.pathBetweenArtistsBFS("Taylor Swift", "Daft Punk");

    std::cout << "BFS path between Taylor Swift and Daft Punk: ";
    for (auto &element : path)
    {
        std::cout << element << " ";
    }
    std::cout << std::endl << "BFS path distance: " << path.size() - 1;

    // path between artists DFS
    // I wouldn't give the option to print the DFS path because it is not ideal,
    // but you can show the distance still (length of path) and the time it takes
    std::list<std::string> pathDFS = graph.pathBetweenArtistsDFS("Taylor Swift", "Daft Punk");

    std::cout << std::endl << "DFS path distance: " << pathDFS.size() - 1;*/

    return 0;
}