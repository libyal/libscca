#!/usr/bin/env python
#
# Python-bindings file type test script
#
# Copyright (C) 2011-2022, Joachim Metz <joachim.metz@gmail.com>
#
# Refer to AUTHORS for acknowledgements.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

import argparse
import os
import sys
import unittest

import pyscca


class FileTypeTests(unittest.TestCase):
  """Tests the file type."""

  def test_signal_abort(self):
    """Tests the signal_abort function."""
    scca_file = pyscca.file()

    scca_file.signal_abort()

  def test_open(self):
    """Tests the open function."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    scca_file = pyscca.file()

    scca_file.open(test_source)

    with self.assertRaises(IOError):
      scca_file.open(test_source)

    scca_file.close()

    with self.assertRaises(TypeError):
      scca_file.open(None)

    with self.assertRaises(ValueError):
      scca_file.open(test_source, mode="w")

  def test_open_file_object(self):
    """Tests the open_file_object function."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    if not os.path.isfile(test_source):
      raise unittest.SkipTest("source not a regular file")

    scca_file = pyscca.file()

    with open(test_source, "rb") as file_object:

      scca_file.open_file_object(file_object)

      with self.assertRaises(IOError):
        scca_file.open_file_object(file_object)

      scca_file.close()

      with self.assertRaises(TypeError):
        scca_file.open_file_object(None)

      with self.assertRaises(ValueError):
        scca_file.open_file_object(file_object, mode="w")

  def test_close(self):
    """Tests the close function."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    scca_file = pyscca.file()

    with self.assertRaises(IOError):
      scca_file.close()

  def test_open_close(self):
    """Tests the open and close functions."""
    test_source = unittest.source
    if not test_source:
      return

    scca_file = pyscca.file()

    # Test open and close.
    scca_file.open(test_source)
    scca_file.close()

    # Test open and close a second time to validate clean up on close.
    scca_file.open(test_source)
    scca_file.close()

    if os.path.isfile(test_source):
      with open(test_source, "rb") as file_object:

        # Test open_file_object and close.
        scca_file.open_file_object(file_object)
        scca_file.close()

        # Test open_file_object and close a second time to validate clean up on close.
        scca_file.open_file_object(file_object)
        scca_file.close()

        # Test open_file_object and close and dereferencing file_object.
        scca_file.open_file_object(file_object)
        del file_object
        scca_file.close()

  def test_get_format_version(self):
    """Tests the get_format_version function and format_version property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    scca_file = pyscca.file()

    scca_file.open(test_source)

    format_version = scca_file.get_format_version()
    self.assertIsNotNone(format_version)

    self.assertIsNotNone(scca_file.format_version)

    scca_file.close()

  def test_get_executable_filename(self):
    """Tests the get_executable_filename function and executable_filename property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    scca_file = pyscca.file()

    scca_file.open(test_source)

    executable_filename = scca_file.get_executable_filename()
    self.assertIsNotNone(executable_filename)

    self.assertIsNotNone(scca_file.executable_filename)

    scca_file.close()

  def test_get_prefetch_hash(self):
    """Tests the get_prefetch_hash function and prefetch_hash property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    scca_file = pyscca.file()

    scca_file.open(test_source)

    prefetch_hash = scca_file.get_prefetch_hash()
    self.assertIsNotNone(prefetch_hash)

    self.assertIsNotNone(scca_file.prefetch_hash)

    scca_file.close()

  def test_get_run_count(self):
    """Tests the get_run_count function and run_count property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    scca_file = pyscca.file()

    scca_file.open(test_source)

    run_count = scca_file.get_run_count()
    self.assertIsNotNone(run_count)

    self.assertIsNotNone(scca_file.run_count)

    scca_file.close()

  def test_get_number_of_file_metrics_entries(self):
    """Tests the get_number_of_file_metrics_entries function and number_of_file_metrics_entries property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    scca_file = pyscca.file()

    scca_file.open(test_source)

    number_of_file_metrics_entries = scca_file.get_number_of_file_metrics_entries()
    self.assertIsNotNone(number_of_file_metrics_entries)

    self.assertIsNotNone(scca_file.number_of_file_metrics_entries)

    scca_file.close()

  def test_get_number_of_filenames(self):
    """Tests the get_number_of_filenames function and number_of_filenames property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    scca_file = pyscca.file()

    scca_file.open(test_source)

    number_of_filenames = scca_file.get_number_of_filenames()
    self.assertIsNotNone(number_of_filenames)

    self.assertIsNotNone(scca_file.number_of_filenames)

    scca_file.close()

  def test_get_number_of_volumes(self):
    """Tests the get_number_of_volumes function and number_of_volumes property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    scca_file = pyscca.file()

    scca_file.open(test_source)

    number_of_volumes = scca_file.get_number_of_volumes()
    self.assertIsNotNone(number_of_volumes)

    self.assertIsNotNone(scca_file.number_of_volumes)

    scca_file.close()


if __name__ == "__main__":
  argument_parser = argparse.ArgumentParser()

  argument_parser.add_argument(
      "source", nargs="?", action="store", metavar="PATH",
      default=None, help="path of the source file.")

  options, unknown_options = argument_parser.parse_known_args()
  unknown_options.insert(0, sys.argv[0])

  setattr(unittest, "source", options.source)

  unittest.main(argv=unknown_options, verbosity=2)
