#include "shared_ptr.hpp"
#include "matrix.hpp"
#include <iostream>
// Storage implement

shared_ptr::Storage::Storage(Matrix* mtx) : data_(mtx), ref_count_(1) {
  // if (mtx != nullptr)
    // incr();
}

shared_ptr::Storage::~Storage() {
  if (data_ != nullptr)
    delete data_;
}

void shared_ptr::Storage::incr() {
  ref_count_++;
}

void shared_ptr::Storage::decr() {
  ref_count_--;
}

int shared_ptr::Storage::getCounter() const {
  return ref_count_;
}

Matrix* shared_ptr::Storage::getObject() const {
  return data_;
}

// shared_ptr implement

shared_ptr::shared_ptr(Matrix* obj) : storage_(new Storage(obj)) {}

void shared_ptr::destroy_() {
  if (storage_->getCounter() > 1)
    storage_->decr();
  else if (storage_ != nullptr)
    delete storage_;
}

shared_ptr::~shared_ptr() {
  destroy_();
}

void shared_ptr::copy_(const shared_ptr& other) {
  storage_ = other.storage_;
  storage_->incr();
}

shared_ptr::shared_ptr(const shared_ptr& other) {
  copy_(other);
}

shared_ptr& shared_ptr::operator=(const shared_ptr& other) {
  if (other.storage_ == storage_) 
    return *this;
  
  destroy_();
  copy_(other);
  
  return *this;
}

Matrix* shared_ptr::ptr() const {
  return storage_->getObject();
}

bool shared_ptr::isNull() const {
  return storage_->getObject() == nullptr;
}

void shared_ptr::reset(Matrix* obj) {
  *this = shared_ptr(obj);
}

Matrix* shared_ptr::operator->() const {
  return storage_->getObject();
}

Matrix& shared_ptr::operator*() const {
  return *(storage_->getObject());
}
