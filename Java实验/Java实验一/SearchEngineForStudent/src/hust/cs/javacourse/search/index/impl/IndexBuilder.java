package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractDocument;
import hust.cs.javacourse.search.index.AbstractDocumentBuilder;
import hust.cs.javacourse.search.index.AbstractIndex;
import hust.cs.javacourse.search.index.AbstractIndexBuilder;
import hust.cs.javacourse.search.util.FileUtil;

import java.io.File;
import java.io.IOException;
import java.util.Collections;
import java.util.List;

public class IndexBuilder extends AbstractIndexBuilder {
    public IndexBuilder(AbstractDocumentBuilder docBuilder) {
        super(docBuilder);
    }

    @Override
    public AbstractIndex buildIndex(String rootDirectory) throws IOException {
        AbstractIndex index = new Index();
        List<String> filePaths = FileUtil.list(rootDirectory);//构建文件夹索引
        Collections.reverse(filePaths);//顺序排列
        AbstractDocument document = null;
        for (String docPath : filePaths) {

            document = docBuilder.build(docId, docPath, new File(docPath));
            index.addDocument(document);//将文件夹中的termtuple倒序构建索引
            docId += 1;
        }
        return index;
    }
}

