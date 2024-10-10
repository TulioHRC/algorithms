fn bubble_sort<T: Default + PartialOrd>(list: &mut Vec<T>) {
  let list_len = list.len();
  for _i in 0..list_len {
    for j in 1..list_len {
      if list[j] < list[j - 1] {
        list.swap(j,j - 1);
      } 
    }
  }
}

#[cfg(test)]
mod tests {
  use super::*;

  #[test]
  fn test_no_element_sort() {
    let mut vector: Vec<i32> = vec![];
    bubble_sort::<i32>(&mut vector);
    assert_eq!(vector, vec![]);
  }

  #[test]
  fn test_one_element_sort() {
    let mut vector: Vec<i32> = vec![0];
    bubble_sort::<i32>(&mut vector);
    assert_eq!(vector, vec![0]);
  }

  #[test]
  fn test_sorted_multiple_elements_sort() {
    let mut vector: Vec<i32> = vec![0, 1, 2];
    bubble_sort::<i32>(&mut vector);
    assert_eq!(vector, vec![0, 1, 2]);
  }

  #[test]
  fn test_reverse_sorted_multiple_elements_sort() {
    let mut vector: Vec<i32> = vec![2, 1, 0];
    bubble_sort::<i32>(&mut vector);
    assert_eq!(vector, vec![0, 1, 2]);
  }

  #[test]
  fn test_multiple_elements_sort() {
    let mut vector: Vec<i32> = vec![2, 3, 5, 10, 1, 0];
    bubble_sort::<i32>(&mut vector);
    assert_eq!(vector, vec![0, 1, 2, 3, 5, 10]);
  }
}