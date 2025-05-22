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

//tab class for document editor
class Tab : public DocumentElement {
public:
    string render() override {
        return "\t";
    }
};


//Document class for DocumentElement
class Document {
private:
    vector<DocumentElement*> elements;
public:
    void addElements(DocumentElement* element) {
        elements.push_back(element);
    }

    //renders the document by checking the type of each element
    string render () {
        string result;
        for (auto& element: elements) {
            result += element -> render();
        }
        return result;
    } 
};


//Persistence (Abstranction) class for saving the document
class Persistence {
public:
    virtual void save (string data) = 0;
};

//implementation of Filestorage class
class FileStorage : public Persistence {
public:
    void save (string data) override {  
        ofstream outFile ("document.txt");
        if (outFile) {
            outFile << data;
            outFile.close();
            cout << "Document saved to document.txt" << endl;
        } else {
            cout << "Error: Unable to open file" << endl;
        }
    }
};

class DatabaseStorage : public Persistence {
public:
    void save (string data) override {
        // Simulate saving to a database
        cout << "Document saved to database: " << data << endl;
    }
};



//DocumentEditor class to manage the document
class DocumentEditor {
private:
    Document* doc;
    Persistence* db;
    string renderedDocument;

public:
    DocumentEditor(Document* doc, Persistence* db) {
       this -> doc = doc;
       this -> db = db;
    }
    void addText(const string& text) {
        doc -> addElements(new TextElement(text));
    }

    void addImage(const string& path) {
        doc -> addElements(new ImageElement(path));
    }

    void addNewLine() {
        doc -> addElements(new NewLine());
    }

    void addTab() {
        doc -> addElements(new Tab());
    }

    //renders the document by checking the type of each element
    string renderDocument() {
        if (renderedDocument.empty())
            renderedDocument = doc -> render();
        return renderedDocument;
    }

    void saveDocument() {
        db -> save(renderDocument());
    }
    
};

int main () {
    Document* document = new Document();
    Persistence* persistence = new FileStorage();
    DocumentEditor* editor = new DocumentEditor(document, persistence);

    //simulating a client using the document editor
    editor -> addText("Hola! this is Ashutosh.");
    editor -> addNewLine();
    editor -> addImage("image1.png");
    editor -> addNewLine();
    editor -> addText("This is a text.");
    editor -> addTab();
    editor -> addImage("image2.jpg");
    editor -> addNewLine();
    editor -> addText("This is another text.");

    cout << editor -> renderDocument() << endl;
    editor -> saveDocument();


    return 0;
}