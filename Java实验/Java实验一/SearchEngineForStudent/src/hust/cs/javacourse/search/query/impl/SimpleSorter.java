package hust.cs.javacourse.search.query.impl;

import hust.cs.javacourse.search.index.AbstractIndex;
import hust.cs.javacourse.search.index.AbstractPosting;
import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.query.AbstractHit;
import hust.cs.javacourse.search.query.Sort;

import java.util.Collections;
import java.util.List;
import java.util.Map;

public class SimpleSorter implements Sort {
    @Override
    public void sort(List<AbstractHit> hits) {
        hits.sort(AbstractHit::compareTo);
    }

    @Override
    public double score(AbstractHit hit) {
        double s = 0;
        for (Map.Entry<AbstractTerm, AbstractPosting> entry : hit.getTermPostingMapping().entrySet()) {
            if (entry.getValue() != null) {
                s += entry.getValue().getFreq();
            }
        }
        // 分数倒置
        return -s;
    }
}
