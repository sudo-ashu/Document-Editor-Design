#include<bits/stdc++.h>
using namespace std;


//Abstraction for document elements
class DocumentElement {
public:
    virtual string render() = 0;
};

//Concrete implementation of text elements
class TextElement: public DocumentElement {
private:
    string text;
public:
    TextElement(const string& text) {
        this -> text = text;
    }
    string render () override {
        return text;
    }
};

class ImageElement: public DocumentElement {
private:
    string imagePath;
public:
    ImageElement(const string& imagePath) {
        this -> imagePath = imagePath;
    }
    string render () override {
        return "[Image: " + imagePath + "]";
    }
};


//NewLine class for document editor
class NewLine : public DocumentElement {
public:
    string render() override {
        return "\n";
    }
};

class DocumentEditor {
private:
    vector<string> docElements;
    string renderedDocument;

public:
    void addText(const string& text) {
        docElements.push_back(text);
    }

    void addImage(const string& path) {
        docElements.push_back(path);
    }

    //renders the document by checking the type of each element
    string renderDocument() {
        if (renderedDocument.empty()) {
            string result;
            for (const auto element: docElements) {
                int n = element.size();

                // Check if the element is a text or an image
                if (n>4 and element.substr(n-4) == ".png" or element.substr(n-4) == ".jpg") {
                    result += "[Image: " + element + "]" + "\n";
                } else
                    result += element + "\n";
            }
            renderedDocument = result;
        }
        return renderedDocument;
    }

    void saveToFile() {
        ofstream outFile("document.txt");
        if (outFile.is_open()) {
            outFile << renderDocument();
            outFile.close();
            cout << "Document saved to document.txt" << endl;
        } else {
            cout << "Error: Unable to open file" << endl;
        }
    }
    
};

int main () {
    DocumentEditor editor;
    editor.addText("Hola! this is Ashutosh.");
    editor.addImage("image1.png");
    editor.addText("This is a text.");
    editor.addImage("image2.jpg");

    cout << editor.renderDocument() << endl;
    editor.saveToFile();


    return 0;
}