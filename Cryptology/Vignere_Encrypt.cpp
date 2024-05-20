#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

// Function to clean the text: remove non-letter characters and convert to lowercase
string cleanText(const string &text)
{
    string cleaned;
    for (char c : text)
    {
        if (isalpha(c))
        {
            cleaned += tolower(c);
        }
    }
    return cleaned;
}

string vigenereEncrypt(const string &plaintext, const string &key)
{
    string cleanedText = cleanText(plaintext);
    string ciphertext;
    for (int i = 0; i < cleanedText.length(); i++)
    {
        int shift = key[i % key.length()] - 'a';
        ciphertext += (cleanedText[i] - 'a' + shift) % 26 + 'a';
    }
    return ciphertext;
}

string formatCiphertext(const string &ciphertext)
{
    string formatted;
    int length = ciphertext.length();
    for (int i = 0; i < length; i++)
    {
        if (i > 0 && i % 8 == 0)
        {
            formatted += ' ';
            if (i % 64 == 0)
            {
                formatted += '\n';
            }
        }
        formatted += ciphertext[i];
    }
    return formatted;
}

int main()
{
    string key = "mykey";

    string plaintext1 = "In computing, plain text is a loose term for data (e.g. file contents) that represent only characters of readable material but not its graphical representation nor other objects (floating-point numbers, images, etc.). It may also include a limited number of  whitespace  characters that affect simple arrangement of text, such as spaces, line breaks, or tabulation characters. Plain text is different from formatted text, where style information is included; from structured text, where structural parts of the document such as paragraphs, sections, and the like are identified; and from binary files in which some portions must be interpreted as binary objects (encoded integers, real numbers, images, etc.). The term is sometimes used quite loosely, to mean files that contain only readable content(or just files with nothing that the speaker does not prefer).For example, that could exclude any indication of fonts or layout(such as markup, markdown, or even tabs); characters such as curly quotes, non - breaking spaces, soft hyphens, em dashes, and / or ligatures; or other things. In principle, plain text can be in any encoding, but occasionally the term is taken to imply ASCII. As Unicode-based encodings such as UTF-8 and UTF-16 become more common, that usage may be shrinking. Plain text is also sometimes used only to exclude binary files: those in which at least some parts of the file cannot be correctly interpreted via the character encoding in effect. For example, a file or string consisting of hello (in any encoding), following by 4 bytes that express a binary integer that is not a character, is a binary file. Converting a plain text file to a different character encoding does not change the meaning of the text, as long as the correct character encoding is used. However, converting a binary file to a different format may alter the interpretation of the non-textual data. Plain text and rich text According to The Unicode Standard:[1] Plain text is a pure sequence of character codes; plain Un-encoded text is therefore a sequence of Unicode character codes. In contrast, styled text, also known as rich text, is any text representation containing plain text plus added information such as a language identifier, font size, color, hypertext links, and so on. SGML, RTF, HTML, XML, and TeX are examples of rich text fully represented as plain text streams, interspersing plain text data with sequences of characters that represent the additional data structures. According to other definitions, however, files that contain markup or other meta-data are generally considered plain text, so long as the markup is also in a directly human-readable form (as in HTML, XML, and so on). Thus, representations such as SGML, RTF, HTML, XML, wiki markup, and TeX, as well as nearly all programming language source code files, are considered plain text. The particular content is irrelevant to whether a file is plain text. For example, an SVG file can express drawings or even bitmapped graphics, but is still plain text. The use of plain text rather than binary files enables files to survive much better in the wild, in part by making them largely immune to computer architecture incompatibilities. For example, all the problems of Endianness can be avoided (with encodings such as UCS-2 rather than UTF-8, endianness matters, but uniformly for every character, rather than for potentially-unknown subsets of it).";
    string plaintext2 = "Usage The purpose of using plain text today is primarily independence from programs that require their very own special encoding or formatting or file format.Plain text files can be opened, read, and edited with ubiquitous text editors and utilities. command - line interface allows people to give commands in plain text and get a response, also typically in plain text. Many other computer programs are also capable of processing or creating plain text, such as countless programs in DOS, Windows, classic Mac OS, and Unix and its kin; as well as web browsers (a few browsers such as Lynx and the Line Mode Browser produce only plain text for display) and other e-text readers. Plain text files are almost universal in programming; a source code file containing instructions in a programming language is almost always a plain text file. Plain text is also commonly used for configuration files, which are read for saved settings at the startup of a program. Plain text is used for much e-mail. A comment, a .txt file, or a TXT Record generally contains only plain text (without formatting) intended for humans to read. The best format for storing knowledge persistently is plain text, rather than some binary format.[2] Encoding Character encodings This section does not cite any sources. Please help improve this section by adding citations to reliable sources. Unsourced material may be challenged and removed. (December 2023) (Learn how and when to remove this message) Main article: Character encoding Before the early 1960s, computers were mainly used for number-crunching rather than for text, and memory was extremely expensive. Computers often allocated only 6 bits for each character, permitting only 64 characters—assigning codes for A-Z, a-z, and 0-9 would leave only 2 codes: nowhere near enough. Most computers opted not to support lower-case letters. Thus, early text projects such as Roberto Busa's Index Thomisticus, the Brown Corpus, and others had to resort to conventions such as keying an asterisk preceding letters actually intended to be upper-case. Fred Brooks of IBM argued strongly for going to 8-bit bytes, because someday people might want to process text, and won. Although IBM used EBCDIC, most text from then on came to be encoded in ASCII, using values from 0 to 31 for (non-printing) control characters, and values from 32 to 127 for graphic characters such as letters, digits, and punctuation. Most machines stored characters in 8 bits rather than 7, ignoring the remaining bit or using it as a checksum. The near-ubiquity of ASCII was a great help, but failed to address international and linguistic concerns. The dollar-sign ($) was not as useful in England, and the accented characters used in Spanish, French, German, Portuguese, and many other languages were entirely unavailable in ASCII (not to mention characters used in Greek, Russian, and most Eastern languages). Many individuals, companies, and countries defined extra characters as needed—often reassigning control characters, or using values in the range from 128 to 255. Using values above 128 conflicts with using the 8th bit as a checksum, but the checksum usage gradually died out. These additional characters were encoded differently in different countries, making texts impossible to decode without figuring out the originator's rules. For instance, a browser might display ¬A rather than ` if it tried to interpret one character set as another. The International Organization for Standardization (ISO) eventually developed several code pages under ISO 8859, to accommodate various languages. The first of these (ISO 8859-1) is also known as Latin-1, and covers the needs of most (not all) European languages that use Latin-based characters (there was not quite enough room to cover them all). ISO 2022 then provided conventions for switching between different character sets in mid-file. Many other organisation developed variations on these, and for many years Windows and Macintosh computers used incompatible variations. The text-encoding situation became more and more complex, leading to efforts by ISO and by the Unicode Consortium to develop a single, unified character encoding that could cover all known (or at least all currently known) languages. After some conflict,[citation needed] these efforts were unified. Unicode currently allows for 1,114,112 code values, and assigns codes covering nearly all modern text writing systems, as well as many historical ones, and for many non-linguistic characters such as printer's dingbats, mathematical symbols, etc. Text is considered plain text regardless of its encoding. To properly understand or process it the recipient must know (or be able to figure out) what encoding was used; however, they need not know anything about the computer architecture that was used, or about the binary structures defined by whatever program (if any) created the data. Perhaps the most common way of explicitly stating the specific encoding of plain text is with a MIME type. For email and HTTP, the default MIME type is text/plain -- plain text without markup. Another MIME type often used in both email and HTTP is text/html; charset=UTF-8 -- plain text represented using the UTF-8 character encoding with HTML markup. Another common MIME type is application/json -- plain text represented using the UTF-8 character encoding with JSON markup. When a document is received without any explicit indication of the character encoding, some applications use charset detection to attempt to guess what encoding was used.";

    string ciphertext1 = vigenereEncrypt(plaintext1, key);
    string ciphertext2 = vigenereEncrypt(plaintext2, key);

    string formattedCiphertext1 = formatCiphertext(ciphertext1);
    string formattedCiphertext2 = formatCiphertext(ciphertext2);

    cout << "Ciphertext 1:\n" << formattedCiphertext1 << "\n";
    cout << "Ciphertext 2:\n" << formattedCiphertext2 << "\n";

    return 0;
}
