#include <iostream>
#include <string>
#include <cmath>

std::string fullEquation; // this contains what the user submits
std::string answer;       // this contains the final answer

// addition and subtraction
std::string addAndSubChecker(std::string partOfEquation) // of pemdas this does as
{
    int base = -1;
    int indexOfSym = base;   // imagine 123-20-1 should give 3
    int indexOfSym2 = base;  // should give 6
    std::string front = "";  // calculates with first -
    std::string middle = ""; // calculates after first -
    std::string back = "";   // leaves for later
    double firstNum = 0;
    double secondNum = 0;

    for (int i = 1; i < partOfEquation.length(); i++) // skips if negative is first
    {
        if ((partOfEquation.substr(i, 1) == "-" || partOfEquation.substr(i, 1) == "+") && indexOfSym == indexOfSym2)
        {
            indexOfSym = i;
        }
        else if ((partOfEquation.substr(i, 1) == "-" || partOfEquation.substr(i, 1) == "+") && indexOfSym != indexOfSym2)
        {
            indexOfSym2 = i;
            i = partOfEquation.length(); // ends loop
        }
    }

    // this is for negative numbers
    // -1 + 12 shouldn't end
    if (partOfEquation.substr(0, 1) == "-" && indexOfSym == base)
    {
        return partOfEquation;
    }

    if (indexOfSym == indexOfSym2)
    { // base case
        // std::cout << "There is no subtraction anymore but here is partOfEquation " << partOfEquation << std::endl; // this ends recursion
        return partOfEquation;
    }
    front = partOfEquation.substr(0, indexOfSym);
    middle = partOfEquation.substr(indexOfSym + 1, indexOfSym2 - indexOfSym - 1);
    if (indexOfSym2 != -1)
    {
        back = partOfEquation.substr(indexOfSym2); // gets after second minus if there is one
    }
    std::cout << "Subtraction or addition -+-+- front: " << front << " middle: " << middle << " back: " << back << std::endl;
    firstNum = std::stod(front);
    secondNum = std::stod(middle);
    if (partOfEquation.substr(indexOfSym, 1) == "-")
    {
        std::cout << front << " - " << middle << " with " << back << " on the back burner " << std::endl;
        front = std::to_string(firstNum - secondNum);
    }
    if (partOfEquation.substr(indexOfSym, 1) == "+")
    {
        std::cout << front << " + " << middle << " with " << back << " on the back burner" << std::endl;
        front = std::to_string(firstNum + secondNum);
    }

    std::cout << front << std::endl;

    return (addAndSubChecker((front) + "" + back));
}

// multiplication and division
std::string mulAndDivChecker(std::string partOfEquation) // of pemdas this does md and sends to as
{
    int base = -1; // to prevent breaking
    int indexOfSym = base;
    int indexOfSym2 = base;
    int indexOfFirstMul = base;

    std::string nothing = ""; // to prevent breaking
    std::string frontMatter = nothing;
    std::string firstNumStr = nothing;
    std::string secondNumStr = nothing;
    std::string symbol = nothing;
    std::string backMatter = nothing;

    double sumNum;

    std::string combineNumStr;

    for (int i = 0; i < partOfEquation.length(); i++) // collects all three indexs and the symbol
    {
        std::string oneChar = partOfEquation.substr(i, 1);
        if ((oneChar == "*" || oneChar == "/") && indexOfFirstMul == base) // makes index of multiplication down
        {
            indexOfFirstMul = i;
            symbol = oneChar;
        }
        else if ((oneChar == "+" || oneChar == "-") && indexOfFirstMul == base)
        { // collects all symbols before multiplication is down
            indexOfSym = i;
        }
        else if ((oneChar == "+" || oneChar == "-" || oneChar == "*" || oneChar == "/") && indexOfSym2 == base)
        { // collects first symbol after multiplication
            indexOfSym2 = i;
        }
    }

    if (indexOfFirstMul == base) // sends down the ladder
    {
        return addAndSubChecker(partOfEquation);
    }

    if (indexOfSym != base) // gets front matter if any
    {
        frontMatter = partOfEquation.substr(0, indexOfSym + 1); // this would take everything before */ (12 + 2 * 5) would take 12+
    }

    firstNumStr = partOfEquation.substr(indexOfSym + 1, indexOfFirstMul - indexOfSym - 1); // should work if or if not front matter

    secondNumStr = partOfEquation.substr(indexOfFirstMul + 1); // gets over written if there is back matter

    if (indexOfSym2 != base) // gets backMatter if any
    {
        secondNumStr = partOfEquation.substr(indexOfFirstMul + 1, indexOfSym2 - indexOfFirstMul - 1); // only works if there is back matter

        backMatter = partOfEquation.substr(indexOfSym2);
    }

    std::cout << std::endl
              << "front matter is " << frontMatter << std::endl;
    std::cout << "first number is " << firstNumStr << std::endl;
    std::cout << "symbol is " << symbol << std::endl;
    std::cout << "second number is " << secondNumStr << std::endl;
    std::cout << "back matter is " << backMatter << std::endl
              << std::endl;

    // backMatter = partOfEquation.subString;
    // std::cout << "index of first Mul: " << indexOfFirstMul << " and that is a " << symbol << std::endl;
    // std::cout << "index of First sym: " << indexOfSym << " and second symbol " << indexOfSym2 << std::endl;

    if (symbol == "*")
    {
        sumNum = std::stod(firstNumStr) * std::stod(secondNumStr);
    }
    if (symbol == "/")
    {
        sumNum = (std::stod(firstNumStr) / std::stod(secondNumStr));
    }

    combineNumStr = std::to_string(sumNum);

    combineNumStr = frontMatter + combineNumStr + backMatter; // holds the new equation;

    std::cout << "sum of numbers: " << combineNumStr << std::endl;

    return mulAndDivChecker(combineNumStr);
}

// exponents
std::string exponentChecker(std::string partOfEquation) // of pemdas this does e and calls md
{
    int base = -1; // to prevent breaking
    int indexOfSym = base;
    int indexOfSym2 = base;
    int indexOfFirstExp = base;

    std::string nothing = ""; // to prevent breaking
    std::string frontMatter = nothing;
    std::string firstNumStr = nothing;
    std::string secondNumStr = nothing;
    std::string symbol = nothing;
    std::string backMatter = nothing;

    double sumNum;

    std::string combineNumStr;

    for (int i = 0; i < partOfEquation.length(); i++) // collects all three indexs and the symbol
    {
        std::string oneChar = partOfEquation.substr(i, 1);
        if ((oneChar == "^") && indexOfFirstExp == base) // makes index of multiplication down
        {
            indexOfFirstExp = i;
            symbol = oneChar;
        }
        else if ((oneChar == "+" || oneChar == "-" || oneChar == "*" || oneChar == "/") && indexOfFirstExp == base)
        { // collects all symbols before multiplication is down
            indexOfSym = i;
        }
        else if ((oneChar == "+" || oneChar == "-" || oneChar == "*" || oneChar == "/") && indexOfSym2 == base)
        { // collects first symbol after multiplication
            indexOfSym2 = i;
        }
    }

    if (indexOfFirstExp == base) // send down the ladder
    {
        return mulAndDivChecker(partOfEquation);
    }

    if (indexOfSym != base) // gets front matter if any
    {
        frontMatter = partOfEquation.substr(0, indexOfSym + 1); // this would take everything before */ (12 + 2 * 5) would take 12+
    }

    firstNumStr = partOfEquation.substr(indexOfSym + 1, indexOfFirstExp - indexOfSym - 1); // should work if or if not front matter

    secondNumStr = partOfEquation.substr(indexOfFirstExp + 1); // gets over written if there is back matter

    if (indexOfSym2 != base) // gets backMatter if any
    {
        secondNumStr = partOfEquation.substr(indexOfFirstExp + 1, indexOfSym2 - indexOfFirstExp - 1); // only works if there is back matter

        backMatter = partOfEquation.substr(indexOfSym2);
    }

    std::cout << std::endl
              << "front matter is " << frontMatter << std::endl;
    std::cout << "first number is " << firstNumStr << std::endl;
    std::cout << "symbol is " << symbol << std::endl;
    std::cout << "second number is " << secondNumStr << std::endl;
    std::cout << "back matter is " << backMatter << std::endl
              << std::endl;

    sumNum = pow(std::stod(firstNumStr), std::stod(secondNumStr));

    combineNumStr = std::to_string(sumNum);

    combineNumStr = frontMatter + combineNumStr + backMatter; // holds the new equation;

    std::cout << "sum of numbers: " << combineNumStr << std::endl;

    return exponentChecker(combineNumStr);
}

// parathesis
std::string parenthesisChecker(std::string partOfEquation, int level)
{

    if (partOfEquation == "")
    {
        return "";
    }
    int pCounter = 0;
    bool hasP = false;
    int indexFirstP = -1;
    int indexLastP = -1;
    std::string front;  // before parenthesis
    std::string middle; // in the parenthesis
    std::string back;   // after the parenthesis

    std::string holder = partOfEquation.substr(0, 1);

    std::cout << "the holder is " << holder << std::endl;
    if (holder == "+" || holder == "-" || holder == "*" || holder == "/" || holder == "^")
    {
        std::cout << "there is a holder that is " << holder << std::endl;
    }

    // on the third round of false for (())

    for (int i = 0; i < partOfEquation.length(); i++)
    {
        if (partOfEquation.substr(i, 1) == "(")
        {
            pCounter++;
            if (hasP == false)
            {
                indexFirstP = i;
                hasP = true;
            }
        }
        if (partOfEquation.substr(i, 1) == ")")
        {
            pCounter--;
            indexLastP = i;
        }
        if (hasP && pCounter == 0)
        {
            i = partOfEquation.length(); // this should end the parenthesis when it gets to zero
        }
    }
    if (!hasP) // no parenthesis
    {
        std::cout << "do math on middle: " << partOfEquation << " level " << level << std::endl;
        // pretend it returns the number 12-5 = 7

        // sends off to next step which is ^
        // std::cout << " send off to ^ " << std::endl;

        return exponentChecker(partOfEquation);
    }
    else
    {
        // front
        if (indexFirstP != 0)
        {
            front = partOfEquation.substr(0, indexFirstP);
        }
        else
        {
            front = "";
        }

        // middle
        // this is where the math happens
        middle = partOfEquation.substr(indexFirstP + 1, indexLastP - indexFirstP - 1);

        // back
        if (indexLastP + 1 < partOfEquation.length())
        {
            back = partOfEquation.substr(indexLastP + 1);
        }

        else
        {
            back = "";
        }
    }

    std::cout << "the front is: " << front << " the middle is: " << middle << ". The back is " << back << std::endl;
    // std::cout << "first index " << indexFirstP << " and second index " << indexLastP << std::endl;

    if (hasP && pCounter == 0 && (indexFirstP != indexLastP)) // this is not a real equation
    {
        return parenthesisChecker(front + parenthesisChecker(middle, level + 1) + parenthesisChecker(back, level + 1), level + 1);

        // return parenthesisChecker(front + parenthesisChecker(middle, level + 1) + parenthesisChecker(back, level + 1), level + 1);
    }

    // std::cout << partOfEquation.substr(indexFirstP + 1, indexLastP - 1) << " " << indexLastP << std::endl;

    return "Incorrect Parenthesis";
    //  end of pcount
}

std::string breaker(std::string partOfEquation) // this should break down pemdas
{                                               //() ^ * / + -

    // the first part removes the parenthesis that are grouping it all together
    return "Output: " + partOfEquation.substr(1, partOfEquation.length() - 2) + " = " + parenthesisChecker(partOfEquation, 0);
}

std::string removalOfWords(std::string partOfEquation) // this removes the excess symbols before the breaker runs
{
    std::string listOfAllowed = "1234567890()^*/+-."; // white listing
    std::string trueEquation = "";
    for (int i = 0; i < partOfEquation.length(); i++)
    {
        for (int j = 0; j < listOfAllowed.length(); j++)
        {
            if (partOfEquation.substr(i, 1) == listOfAllowed.substr(j, 1))
            {
                trueEquation += listOfAllowed.substr(j, 1);
            }
        }
    }

    if (trueEquation == "")
    {
        std::cout << "there is nothing to calculate" << std::endl;
        return "";
    }

    std::cout << "this is what you are trying to solve: "
              << trueEquation << std::endl;

    return trueEquation; // removes all the useless symbols
}

std::string ask() // this gets the equation from the user and sends it to the breaker
{
    std::string checker;

    std::cout << "What would you like to calculate?" << std::endl;

    std::getline(std::cin, fullEquation);
    if (fullEquation != "nothing" && fullEquation != "quit") // this ends the
    {
        // fullEquation = "12+4^2/2-2^3/2";
        fullEquation = removalOfWords(fullEquation); // this results in fullEquation to be what the user wants without the random symbols

        if (fullEquation != "")
        {
            // std::cout << "before breaker" << std::endl;
            std::cout << breaker("(" + fullEquation + ")") << std::endl; // full equation
            // std::cout << "After breaker" << std::endl;
        }
    }

    return fullEquation;
}

// runs the code at the end
int main()
{

    // collection of data
    bool calculating = true;
    while (calculating) // makes sure it asks the question until no more calculations need to be done
    {

        std::string checker;

        checker = ask();
        if (checker == "quit" || checker == "nothing")
        {
            calculating = false;
        }
    }

    return 0;
}