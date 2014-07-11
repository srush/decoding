import pydecode
import time
import pydecode.nlp.dependency_parsing as dep
import pydecode.nlp.tagging as tag
#import pydecode.nlp.permutation as perm
import pydecode.nlp.decoding as decoding
import numpy as np

def make_parsing_dp():
    problem = dep.DependencyProblem(60)
    parser = dep.FirstOrderDecoder()
    scores = np.random.random(parser.output_coder(problem).shape_)
    dp = parser.dynamic_program(problem)
    return dp, scores


def make_tagging_dp():
    problem = tag.TaggingProblem(50, [1]+[50]*48+[1])
    tagger = tag.BigramTagger()
    scores = np.random.random(tagger.output_coder(problem).shape_)
    dp = tagger.dynamic_program(problem)
    return dp, scores

def time_argmax(dp, scores):
    chart = np.zeros(len(dp.hypergraph.edges))
    print dp.items.shape
    for _ in range(1000):
        pydecode.argmax(dp, scores, chart=chart)

def time_argmax_masked(dp, scores):
    chart = np.zeros(len(dp.hypergraph.edges))
    print dp.items.shape
    mask = np.array(np.random.choice([0, 0, 0, 0, 1],
                                     dp.items.shape),
                    dtype=np.uint8)

    for _ in range(1000):
        pydecode.argmax(dp, scores, chart=chart, mask=mask)

def time_hypergraph(dp, scores):
    chart = np.zeros(len(dp.hypergraph.vertices))
    for _ in range(1000):
        pydecode.best_path(dp.hypergraph, scores,
                           chart=chart)

def time_hypergraph_masked(dp, scores):
    chart = np.zeros(len(dp.hypergraph.vertices))
    mask = np.array(np.random.choice([0] * 40 + [1] * 2,
                                     len(dp.hypergraph.vertices)),
                    dtype=np.uint8)
    print  np.sum(mask) / float(len(mask))
    for _ in range(1000):
        pydecode.best_path(dp.hypergraph, scores,
                           chart=chart, mask=mask)


def main():
    dp, scores = make_tagging_dp()
    s = time.time()
    time_argmax(dp, scores)
    print time.time() - s

    hypergraph_scores = np.random.random(len(dp.hypergraph.edges))
    # s = time.time()
    # time_hypergraph(dp, hypergraph_scores)
    # print time.time() - s

    # s = time.time()
    # time_hypergraph_masked(dp, hypergraph_scores)
    # print time.time() - s


if __name__ == "__main__":
    main()

# time 1000 with 11.93
