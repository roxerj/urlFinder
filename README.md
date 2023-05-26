#URL FINDER

A program that extracts all URLs from a given text, that start with "https://", "http://" and "www.", and all words that appear in text 2 or more times.
Result: txt file with extracted URLs and a cross-table that contains all words that appear more than 1 time, their count and rows, in which the words are found.

#USING THE PROGRAM

1) Find the text that you want to test, put it into a txt file and place the file in the program's directory
2) Simply enter "make" into your console when in program directory. Make sure you have MAKE tools installed
3) Enter the txt file's name
4) The results will be output to "rezultatai.txt" file

#EXAMPLE

OpenAI is a distinguished artificial intelligence research lab. They have made significant strides in the development of AI technologies, including the impressive GPT language models. The main mission of OpenAI is to ensure that artificial general intelligence (AGI) is used to the benefit of all of humanity, while always maintaining a strong focus on safety and cooperation in AI development.

For an in-depth understanding of OpenAI's mission, projects, and their latest advancements in AI, visit their official website at https://www.openai.com. To dive into the specifics of their ongoing research and breakthroughs, explore their research page at https://openai.com/research. OpenAI continues to push the boundaries of what's possible in AI, fostering a future where AGI contributes positively to society.

#RESULTS WITH GIVEN EXAMPLE

LINKS (2)
https://openai.com/research
https://www.openai.com

WORD COUNTER
| Word         | Count | Found in rows |
|--------------|-------|---------------|
| a            | 3     | 1 1 3         |
| agi          | 2     | 1 3           |
| ai           | 4     | 1 1 3 3       |
| and          | 3     | 1 3 3         |
| artificial   | 2     | 1 1           |
| at           | 2     | 3 3           |
| development  | 2     | 1 1           |
| in           | 4     | 1 1 3 3       |
| intelligence | 2     | 1 1           |
| is           | 3     | 1 1 1         |
| mission      | 2     | 1 3           |
| of           | 7     | 1 1 1 1 3 3 3 |
| openai       | 3     | 1 1 3         |
| research     | 3     | 1 3 3         |
| the          | 6     | 1 1 1 1 3 3   |
| their        | 4     | 3 3 3 3       |
| to           | 5     | 1 1 3 3 3     |

