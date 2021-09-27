#include <iostream>
#include <fstream>

using namespace std;

struct Segment {
	int ind;
	int start;
	int length;
	bool is_free;

	Segment* prev;
	Segment* next;

	Segment(int ind, int start, int length, bool is_free, Segment* prev, Segment* next) {
		this->ind = ind;
		this->start = start;
		this->length = length;
		this->is_free = is_free;
		this->prev = prev;
		this->next = next;

		if (prev) {
			prev->next = this;
		}
		if (next) {
			next->prev = this;
		}
	}

	void remove() {
		if (prev) {
			prev->next = next;
		}
		if (next) {
			next->prev = prev;
		}
	}
};

Segment* requests[100000];
Segment* free_segments[100000];

void swap(int a, int b) {
	Segment* t = free_segments[a];
	free_segments[a] = free_segments[b];
	free_segments[b] = t;
	free_segments[a]->ind = a;
	free_segments[b]->ind = b;
}

bool segment_comp(Segment* a, Segment* b) {
	return a->length < b->length;
}

int parent(int i) {
	return (i - 1) / 2;
}

int left(int i) {
	return 2 * i + 1;
}

int right(int i) {
	return 2 * i + 2;
}

void siftdown(Segment** heap, int n, int i) {
	int j = i;
	if (left(i) < n && segment_comp(heap[j], heap[left(i)])) {
		j = left(i);
	}
	if (right(i) < n && segment_comp(heap[j], heap[right(i)])) {
		j = right(i);
	}
	if (i != j) {
		swap(i, j);
		siftdown(heap, n, j);
	}
}

void siftup(Segment** heap, int i) {
	while (i > 0 && segment_comp(heap[parent(i)], heap[i])) {
		swap(i, parent(i));
		i = parent(i);
	}
}

void heap_remove(Segment** heap, int& n, int i) {
	swap(i, n - 1);
	n--;
	if (i >= n)
		return;
	siftup(heap, i);
	siftdown(heap, n, i);
}

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	int n, m;
	fin >> n >> m;

	int current_free = 0;
	Segment first_segment = { current_free, 0, n, true, nullptr, nullptr };
	free_segments[current_free++] = &first_segment;

	for (int i = 0; i < m; i++) {
		int current;
		fin >> current;
		if (current > 0) {
			Segment* max_segment = free_segments[0];
			if (!current_free || max_segment->length < current) {
				requests[i] = nullptr;
				fout << -1 << endl;
			} else {
				requests[i] = new Segment(-1, max_segment->start, current, false, max_segment->prev, max_segment);
				fout << requests[i]->start + 1 << endl;
				max_segment->start += current;
				max_segment->length -= current;
				if (max_segment->length > 0) {
					siftdown(free_segments, current_free, max_segment->ind);
				} else {
					max_segment->remove();
					heap_remove(free_segments, current_free, 0);
				}
			}
		} else {
			current = -current;
			Segment* segment_to_free = requests[current - 1];
			if (segment_to_free == nullptr) {
				continue;
			}
			bool prev_free = segment_to_free->prev && segment_to_free->prev->is_free;
			bool next_free = segment_to_free->next && segment_to_free->next->is_free;
			if (!prev_free && !next_free) {
				segment_to_free->is_free = true;
				segment_to_free->ind = current_free;
				free_segments[current_free] = segment_to_free;
				siftup(free_segments, current_free++);
			} else if (!prev_free) {
				segment_to_free->next->start = segment_to_free->start;
				segment_to_free->next->length += segment_to_free->length;
				siftup(free_segments, segment_to_free->next->ind);
				segment_to_free->remove();
			} else if (!next_free) {
				segment_to_free->prev->length += segment_to_free->length;
				siftup(free_segments, segment_to_free->prev->ind);
				segment_to_free->remove();
			} else {
				segment_to_free->prev->length += segment_to_free->length + segment_to_free->next->length;
				siftup(free_segments, segment_to_free->prev->ind);
				segment_to_free->remove();
				heap_remove(free_segments, current_free, segment_to_free->next->ind);
				segment_to_free->next->remove();
			}
			requests[i] = nullptr;
		}
	}

	fin.close();
	fout.close();
}
