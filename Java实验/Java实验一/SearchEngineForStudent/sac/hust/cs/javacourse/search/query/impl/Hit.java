package hust.cs.javacourse.search.query.impl;

import hust.cs.javacourse.search.index.AbstractPosting;
import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.query.AbstractHit;
import hust.cs.javacourse.search.util.FileUtil;
import hust.cs.javacourse.search.util.StringSplitter;

import java.util.Map;

public class Hit extends AbstractHit {
    public Hit(){}

    public Hit(int docId, String docPath){
        super(docId, docPath);
    }
    public Hit(int docId, String docPath, Map<AbstractTerm, AbstractPosting> termPostingMapping){
        super(docId, docPath, termPostingMapping);
    }
    @Override
    public int getDocId() {
        return docId;
    }

    @Override
    public String getDocPath() {
        return docPath;
    }

    @Override
    public String getContent() {
        return content;
    }

    @Override
    public void setContent(String content) {
        this.content = content;
    }

    @Override
    public double getScore() {
        return score;
    }

    @Override
    public void setScore(double score) {
        this.score = score;
    }

    @Override
    public Map<AbstractTerm, AbstractPosting> getTermPostingMapping() {
        return termPostingMapping;
    }

    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        builder.append("\n--------------------------------------");
        builder.append("\n\ndocId: ").append(docId).append("\n\ndocPath: ").append(docPath)
                .append("\n\ncontent: ").append(content).append("\n\nscore: ").append(score).append("\n\n");
        for (Map.Entry<AbstractTerm, AbstractPosting> entry: termPostingMapping.entrySet()) {
            builder.append(entry.getKey().getContent()).append("\t---->\t").append(entry.getValue()).append("\n");
        }
        return builder.toString();
    }

    @Override
    public int compareTo(AbstractHit o) {
        return (int) (getScore() - o.getScore());
    }
}
